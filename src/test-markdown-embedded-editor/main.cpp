
#include <QApplication>
#include <QFile>
#include <QIODevice>

#include <markdown-editor/markdown_editor.h>
#include <markdown-viewer/markdown_viewer_options.h>

using namespace organic;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    QFile f(":/test.md");
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QString all = f.readAll();

    MarkdownEditor w;
    MarkdownViewerOptions options;
    w.set_options(&options);
    w.set_theme("Solarized Light");
    w.set_markdown_content(all);
    w.show();

    return a.exec();
}
