
#include "markdown_embedded_editor.h"
#include "ui_markdown_embedded_editor.h"
#include "view_synchronizer.h"
#include "theme/theme.h"
#include "theme/theme_collection.h"
#include "theme/style_manager.h"


namespace organic
{

MarkdownEmbeddedEditor::MarkdownEmbeddedEditor(QWidget *parent)
    : QWidget(parent), _ui(new Ui::MarkdownEmbeddedEditor), _theme_collection(new ThemeCollection)
{
    _ui->setupUi(this);
    _ui->textedit_markdown->set_parent_editor(this);
    _ui->viewer_markdown->set_parent_editor(this);

    // Balence the splitter
    QList<int> sizes;
    sizes << 100 << 100;
    _ui->splitter->setSizes(sizes);

    // Setup themes
    _theme_collection->load(":/markdown-editor/builtin-htmlpreview-themes.json");

    connect(_ui->textedit_markdown, SIGNAL(trigger_saving()),
            this, SIGNAL(trigger_saving()));

    // Content change signal
    connect(_ui->textedit_markdown->document(), SIGNAL(contentsChanged()),
            this, SLOT(textedit_text_changed()));

#if WITH_QTWEBENGINE
    // XXX 当页面加载完成后，QWebEngineView 总是会夺取焦点，需要禁用
    connect(_ui->viewer_markdown, SIGNAL(loadFinished(bool)),
            this, SLOT(viewer_load_finished()));
#endif

    // Synchronizer
    _view_synchronizer = new ViewSynchronizer(_ui->textedit_markdown, _ui->viewer_markdown, this);

    // Actions
    connect(_ui->action_preview, SIGNAL(triggered(bool)),
            this, SLOT(show_preview()));
    connect(_ui->action_fullscreen,SIGNAL(triggered(bool)),
            this, SLOT(toggle_fullscreen()));
    if (NULL != parent)
        _ui->action_fullscreen->setVisible(false);
}

MarkdownEmbeddedEditor::~MarkdownEmbeddedEditor()
{
    delete _theme_collection;
    delete _ui;
}

bool MarkdownEmbeddedEditor::canInsertFromMimeData(const QMimeData *source) const
{
    return false;
}

void MarkdownEmbeddedEditor::insertFromMimeData(const QMimeData *source)
{
    // default do nothing
}

QTextCursor MarkdownEmbeddedEditor::textCursor() const
{
    return _ui->textedit_markdown->textCursor();
}

QTextDocument* MarkdownEmbeddedEditor::document() const
{
    return _ui->textedit_markdown->document();
}

QString MarkdownEmbeddedEditor::post_process_html(const QString& html)
{
    return html;
}

void MarkdownEmbeddedEditor::textedit_text_changed()
{
    if (_ui->viewer_markdown->isVisible())
    {
        const QString text = _ui->textedit_markdown->toPlainText();
        _ui->viewer_markdown->set_markdown_content(text);
#if WITH_QTWEBENGINE
        _ui->viewer_markdown->setEnabled(false);
#endif
        _viewer_need_update = false;
    }
    else
    {
        _viewer_need_update = true;
    }

    setWindowModified(_ui->textedit_markdown->document()->isModified());
}

#if WITH_QTWEBENGINE
void MarkdownEmbeddedEditor::viewer_load_finished()
{
    _ui->viewer_markdown->setEnabled(true);
    _ui->textedit_markdown->setFocus();
}
#endif

void MarkdownEmbeddedEditor::set_options(MarkdownViewerOptions *options)
{
    _ui->viewer_markdown->set_options(options);
}

void MarkdownEmbeddedEditor::set_theme(const QString &theme)
{
    _current_theme = _theme_collection->theme(theme);

    QString markdown_highlighting = StyleManager::markdownHighlightingPath(_current_theme);
    QString code_highlighting = StyleManager::codeHighlightingPath(_current_theme);
    QString preview_stylesheet = StyleManager::previewStylesheetPath(_current_theme);

    _ui->textedit_markdown->load_style_from_stylesheet(
                markdown_textedit_style_path(markdown_highlighting));
    _ui->viewer_markdown->set_code_highlighting_style(code_highlighting);
    _ui->viewer_markdown->set_theme_css_url(preview_stylesheet);
}

QString MarkdownEmbeddedEditor::markdown_textedit_style_path(const QString &name)
{
    const bool source_at_single_size = false;
    QString suffix = (source_at_single_size ? "" : "+");
    return QString(":/markdown-textedit/theme/%1%2.txt").arg(name).arg(suffix);
}

void MarkdownEmbeddedEditor::set_markdown_content(const QString &md)
{
    _ui->textedit_markdown->setPlainText(md);
    _ui->viewer_markdown->set_markdown_content(md);
}

QString MarkdownEmbeddedEditor::get_markdown_content() const
{
    return _ui->textedit_markdown->toPlainText();
}

void MarkdownEmbeddedEditor::show_preview()
{
    const bool visible = !_ui->viewer_markdown->isVisible();
    _ui->viewer_markdown->setVisible(visible);
    _ui->action_preview->setChecked(visible);

    if (visible && _viewer_need_update)
        textedit_text_changed();
}

void MarkdownEmbeddedEditor::toggle_fullscreen()
{
    Qt::WindowState new_state = (windowState() == Qt::WindowFullScreen ?
                                     Qt::WindowNoState : Qt::WindowFullScreen);
    setWindowState(new_state);
    _ui->action_fullscreen->setChecked(new_state == Qt::WindowFullScreen);
}

}
