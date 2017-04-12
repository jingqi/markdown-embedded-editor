
#include <assert.h>

#include <QScrollBar>

#include <markdown-textedit/markdown_textedit.h>
#include <markdown-viewer/markdown_viewer.h>

#if WITH_QTWEBENGINE
#   include <QWebChannel>
#else
#   include <QWebFrame>
#endif

#include "view_synchronizer.h"


namespace organic
{

ViewSynchronizer::ViewSynchronizer(MarkdownTextEdit *textedit, MarkdownViewer *viewer, QObject *parent)
    : QObject(parent), _textedit(textedit), _viewer(viewer)
{
    assert(NULL != textedit && NULL != viewer);

    // Synchronize scrollbars
    connect(textedit->verticalScrollBar(), SIGNAL(valueChanged(int)),
                this, SLOT(textedit_scrolled()));

    // Restore scrollbar position after content size changed
#if WITH_QTWEBENGINE
#   if QT_VERSION >= 0x050700
    // XXX Signal "contentsSizeChanged()" introduced since QT 5.7
    connect(_viewer->page(), SIGNAL(contentsSizeChanged(QSize)),
            this, SLOT(viewer_content_size_changed()));
#   else
    connect(_viewer, SIGNAL(loadFinished(bool)),
            this, SLOT(viewer_content_size_changed()));
#   endif
#else
    connect(_viewer->page()->mainFrame(), SIGNAL(contentsSizeChanged(QSize)),
            this, SLOT(viewer_content_size_changed()));
#endif

    // Add our objects everytime JavaScript environment is cleared
#if WITH_QTWEBENGINE
    add_javascript_object();
#else
    connect(_viewer->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
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
    _viewer->page()->runJavaScript(js.arg(percent));
#else
    const int viewer_max = _viewer->page()->mainFrame()->scrollBarMaximum(Qt::Vertical);
    const int text_max = _textedit->verticalScrollBar()->maximum();
    const double factor = ((double) viewer_max) / text_max;
    _viewer->page()->mainFrame()->setScrollBarValue(Qt::Vertical, qRound(text_value * factor));
#endif
}

void ViewSynchronizer::viewer_content_size_changed()
{
    // Restore previous scrollbar position
    textedit_scrolled();
}

#if WITH_QTWEBENGINE
void ViewSynchronizer::viewer_scrolled(double percent)
{
    if (!_viewer->hasFocus())
        return;
    const int text_max = _textedit->verticalScrollBar()->maximum();
    _textedit->verticalScrollBar()->setValue(qRound(text_max * percent));
}
#else
void ViewSynchronizer::viewer_scrolled()
{
    if (!_viewer->hasFocus())
        return;
    const double factor = (double) _textedit->verticalScrollBar()->maximum() /
                    _viewer->page()->mainFrame()->scrollBarMaximum(Qt::Vertical);
    const int value = _viewer->page()->mainFrame()->scrollBarValue(Qt::Vertical);
    _textedit->verticalScrollBar()->setValue(qRound(value * factor));
}
#endif

void ViewSynchronizer::add_javascript_object()
{
    // Install JS object
#if WITH_QTWEBENGINE
    QWebChannel *channel = new QWebChannel(_viewer);
    _viewer->page()->setWebChannel(channel);
    channel->registerObject("synchronizer", this);
#else
    _viewer->page()->mainFrame()->addToJavaScriptWindowObject("synchronizer", this);
#endif
}

}
