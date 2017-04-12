
#ifndef ___HEADFILE_EC7146B1_FBB9_44C7_AA75_84EE274EE145_
#define ___HEADFILE_EC7146B1_FBB9_44C7_AA75_84EE274EE145_

#include <markdown_textedit.h>


namespace organic
{

class MarkdownEmbeddedEditor;

class MarkdownTextEditWrapper : public MarkdownTextEdit
{
    Q_OBJECT

    MarkdownEmbeddedEditor *_parent_editor = NULL;

public:
    MarkdownTextEditWrapper(QWidget *parent);

    void set_parent_editor(MarkdownEmbeddedEditor *editor);

protected:
    virtual bool canInsertFromMimeData(const QMimeData *source) const override;
    virtual void insertFromMimeData(const QMimeData *source) override;
};

}

#endif
