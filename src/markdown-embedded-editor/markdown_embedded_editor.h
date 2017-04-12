
#ifndef ___HEADFILE_C33DE701_BD5C_41B8_AB62_C8E462D3047B_
#define ___HEADFILE_C33DE701_BD5C_41B8_AB62_C8E462D3047B_

#include <QWidget>
#include <QMimeData>
#include <QTextCursor>
#include <QTextDocument>

#include <markdown-viewer/markdown_viewer_config.h>

#include "markdown_editor_config.h"
#include "theme/theme.h"

namespace Ui {
class MarkdownEditor;
}

namespace organic
{

class MarkdownViewerOptions;
class ViewSynchronizer;
class ThemeCollection;

class MDE_API MarkdownEditor : public QWidget
{
    Q_OBJECT

    Ui::MarkdownEditor *_ui = NULL;
    ViewSynchronizer *_view_synchronizer = NULL;
    bool _viewer_need_update = false;

    ThemeCollection *_theme_collection = NULL;
    Theme _current_theme { "Default", "Default", "Default", "Default" };

public:
    MarkdownEditor(QWidget *parent=NULL);
    ~MarkdownEditor();

    void set_options(MarkdownViewerOptions *options);
    void set_theme(const QString& theme);
    void set_markdown_content(const QString& md);
    QString get_markdown_content() const;

    virtual bool canInsertFromMimeData(const QMimeData *source) const;
    virtual void insertFromMimeData(const QMimeData *source);
    QTextCursor textCursor() const;
    QTextDocument* document() const;
    virtual QString post_process_html(const QString& html);

private:
    QString markdown_textedit_style_path(const QString &name);

signals:
    void trigger_saving();

private slots:
    void textedit_text_changed();
#if !MARKDOWN_VIEWER_USE_QTWEBKIT
    void viewer_load_finished();
#endif

    void show_preview();
    void toggle_fullscreen();
};

}

#endif
