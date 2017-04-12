
#include <assert.h>

#include "markdown_viewer_wrapper.h"
#include "markdown_embedded_editor.h"

namespace organic
{

MarkdownViewerWrapper::MarkdownViewerWrapper(QWidget *parent)
    : MarkdownViewer(parent)
{
    assert(NULL != parent);
}

void MarkdownViewerWrapper::set_parent_editor(MarkdownEmbeddedEditor *editor)
{
    assert(NULL != editor);
    _parent_editor = editor;
}

QString MarkdownViewerWrapper::post_process_html(const QString& html)
{
    return _parent_editor->post_process_html(html);
}

}
