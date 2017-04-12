
#ifndef ___HEADFILE_8AC25BD6_22FC_42ED_A7CB_3329B6E452A7_
#define ___HEADFILE_8AC25BD6_22FC_42ED_A7CB_3329B6E452A7_

#include <markdown_viewer.h>


namespace organic
{

class MarkdownEmbeddedEditor;

class MarkdownViewerWrapper : public MarkdownViewer
{
    Q_OBJECT

    MarkdownEmbeddedEditor *_parent_editor = NULL;

public:
   MarkdownViewerWrapper(QWidget *parent);

   void set_parent_editor(MarkdownEmbeddedEditor *editor);

protected:
   virtual QString post_process_html(const QString& html) override;
};

}

#endif
