
#include <assert.h>

#include "markdown_textedit_wrapper.h"
#include "markdown_editor.h"


namespace organic
{

MarkdownTextEditWrapper::MarkdownTextEditWrapper(QWidget *parent)
    : MarkdownTextEdit(parent)
{
    assert(NULL != parent);
}

void MarkdownTextEditWrapper::set_parent_editor(MarkdownEditor *editor)
{
    assert(NULL != editor);
    _parent_editor = editor;
}

bool MarkdownTextEditWrapper::canInsertFromMimeData(const QMimeData *source) const
{
    return _parent_editor->canInsertFromMimeData(source) ||
        MarkdownTextEdit::canInsertFromMimeData(source);
}

void MarkdownTextEditWrapper::insertFromMimeData(const QMimeData *source)
{
    if (_parent_editor->canInsertFromMimeData(source))
    {
        _parent_editor->insertFromMimeData(source);
        return;
    }
    MarkdownTextEdit::insertFromMimeData(source);
}

}
