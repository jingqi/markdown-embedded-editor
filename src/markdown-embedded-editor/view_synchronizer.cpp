
#include <assert.h>

#include <QScrollBar>

#include <markdown_textedit.h>
#include <markdown_view.h>

#if WITH_QTWEBENGINE
#   include <QWebChannel>
#else
#   include <QWebFrame>
#endif

#include "view_synchronizer.h"


namespace mdee
{

ViewSynchronizer::ViewSynchronizer(mdtextedit::MarkdownTextEdit *textedit,
                                   mdview::MarkdownView *view, QObject *parent)
    : QObject(parent), _textedit(textedit), _view(view)
{
    assert(NULL != textedit && NULL != view);

    // Synchronize scrollbars
    connect(textedit->verticalScrollBar(), SIGNAL(valueChanged(int)),
                this, SLOT(textedit_scrolled()));

    // Restore scrollbar position after content size changed
#if WITH_QTWEBENGINE
#   if QT_VERSION >= 0x050700
    // XXX Signal "contentsSizeChanged()" introduced since QT 5.7
    connect(_view->page(), SIGNAL(contentsSizeChanged(QSizeF)),
            this, SLOT(view_content_size_changed()));
#   else
    connect(_view, SIGNAL(loadFinished(bool)),
            this, SLOT(view_content_size_changed()));
#   endif
#else
    connect(_view->page()->mainFrame(), SIGNAL(contentsSizeChanged(QSize)),
            this, SLOT(view_content_size_changed()));
#endif

    // Add our objects everytime JavaScript environment is cleared
#if WITH_QTWEBENGINE
    add_javascript_object();
#else
    connect(_view->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
            this, SLOT(add_javascript_object()));
#endif
}

void ViewSynchronizer::textedit_scrolled()
{
    if (!_textedit->hasFocus())
        return;
    const int text_value = _textedit->verticalScrollBar()->value();
#if WITH_QTWEBENGINE
    const int text_max = _textedit->verticalScrollBar()->maximum();
    const double percent = ((double) text_value) / text_max;
    QString js("window.scrollTo(0, document.body.scrollHeight * %1);");
    _view->page()->runJavaScript(js.arg(percent));
#else
    const int view_max = _view->page()->mainFrame()->scrollBarMaximum(Qt::Vertical);
    const int text_max = _textedit->verticalScrollBar()->maximum();
    const double factor = ((double) view_max) / text_max;
    _view->page()->mainFrame()->setScrollBarValue(Qt::Vertical, qRound(text_value * factor));
#endif
}

void ViewSynchronizer::view_content_size_changed()
{
    // Restore previous scrollbar position
    textedit_scrolled();
}

#if WITH_QTWEBENGINE
void ViewSynchronizer::view_scrolled(double percent)
{
    if (!_view->hasFocus())
        return;
    const int text_max = _textedit->verticalScrollBar()->maximum();
    _textedit->verticalScrollBar()->setValue(qRound(text_max * percent));
}
#else
void ViewSynchronizer::view_scrolled()
{
    if (!_view->hasFocus())
        return;
    const double factor = (double) _textedit->verticalScrollBar()->maximum() /
                    _view->page()->mainFrame()->scrollBarMaximum(Qt::Vertical);
    const int value = _view->page()->mainFrame()->scrollBarValue(Qt::Vertical);
    _textedit->verticalScrollBar()->setValue(qRound(value * factor));
}
#endif

void ViewSynchronizer::add_javascript_object()
{
    // Install JS object
#if WITH_QTWEBENGINE
    QWebChannel *channel = new QWebChannel(_view);
    _view->page()->setWebChannel(channel);
    channel->registerObject("synchronizer", this);
#else
    _view->page()->mainFrame()->addToJavaScriptWindowObject("synchronizer", this);
#endif
}

}
