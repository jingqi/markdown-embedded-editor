
#ifndef ___HEADFILE_EC7146B1_FBB9_44C7_AA75_84EE274EE145_
#define ___HEADFILE_EC7146B1_FBB9_44C7_AA75_84EE274EE145_

#include <markdown-textedit/markdown_textedit.h>


namespace organic
{

class MarkdownEditor;

class MarkdownTextEditWrapper : public MarkdownTextEdit
{
    Q_OBJECT

    MarkdownEditor *_parent_editor = NULL;

public:
    MarkdownTextEditWrapper(QWidget *parent);

    void set_parent_editor(MarkdownEditor *editor);

protected:
    virtual bool canInsertFromMimeData(const QMimeData *source) const override;
    virtual void insertFromMimeData(const QMimeData *source) override;
};

}

#endif
