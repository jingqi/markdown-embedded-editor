
#ifndef ___HEADFILE_144C9E35_E907_4EB6_AB89_3855ABE01C75_
#define ___HEADFILE_144C9E35_E907_4EB6_AB89_3855ABE01C75_

#include <QObject>

#include <markdown-viewer/markdown_viewer_config.h>

namespace organic
{

class MarkdownTextEdit;
class MarkdownViewer;

class ViewSynchronizer : public QObject
{
    Q_OBJECT

    MarkdownTextEdit *_textedit = NULL;
    MarkdownViewer *_viewer = NULL;

public:
    ViewSynchronizer(MarkdownTextEdit *textedit, MarkdownViewer *viewer, QObject *parent);

public slots:
    void textedit_scrolled();

    // This slot is called from JS
#if MARKDOWN_VIEWER_USE_QTWEBKIT
    void viewer_scrolled();
#else
    void viewer_scrolled(double percent);
#endif

private slots:
    void viewer_content_size_changed();
    void add_javascript_object();
};


}

#endif
