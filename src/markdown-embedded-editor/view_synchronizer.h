﻿
#ifndef ___HEADFILE_144C9E35_E907_4EB6_AB89_3855ABE01C75_
#define ___HEADFILE_144C9E35_E907_4EB6_AB89_3855ABE01C75_

#include <QObject>

namespace mdtextedit
{
class MarkdownTextEdit;
}

namespace mdview
{
class MarkdownView;
}

namespace mdee
{

class ViewSynchronizer : public QObject
{
    Q_OBJECT

    mdtextedit::MarkdownTextEdit *_textedit = NULL;
    mdview::MarkdownView *_view = NULL;

public:
    ViewSynchronizer(mdtextedit::MarkdownTextEdit *textedit, mdview::MarkdownView *view, QObject *parent);

public slots:
    void textedit_scrolled();

    // This slot is called from JS
#if WITH_QTWEBENGINE
    void view_scrolled(double percent);
#else
    void view_scrolled();
#endif

private slots:
    void view_content_size_changed();
    void add_javascript_object();
};


}

#endif
