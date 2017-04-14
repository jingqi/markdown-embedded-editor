
#include <assert.h>

#include "markdown_view_wrapper.h"
#include "markdown_embedded_editor.h"

namespace mdee
{

MarkdownViewWrapper::MarkdownViewWrapper(QWidget *parent)
    : MarkdownView(parent)
{
    assert(NULL != parent);
}

void MarkdownViewWrapper::set_parent_editor(MarkdownEmbeddedEditor *editor)
{
    assert(NULL != editor);
    _parent_editor = editor;
}

QString MarkdownViewWrapper::post_process_html(const QString& html)
{
    return _parent_editor->post_process_html(html);
}

}
