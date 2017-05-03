
TEMPLATE = subdirs

MARKDOWN_TEXTEDIT_PRO = ../3rdparty/markdown-textedit.git/src/markdown-textedit.pro
MARKDOWN_VIEW_PRO = ../3rdparty/markdown-view.git/src/markdown-view.pro

SUBDIRS += \
    $${MARKDOWN_TEXTEDIT_PRO} \
    $${MARKDOWN_VIEW_PRO} \
    markdown-embedded-editor \
    test-markdown-embedded-editor \
    hunspell \
    markdown-editor

markdown-embedded-editor.depends = $${MARKDOWN_TEXTEDIT_PRO} $${MARKDOWN_VIEW_PRO}
test-markdown-embedded-editor.depends = markdown-embedded-editor
markdown-editor.depends = $${MARKDOWN_TEXTEDIT_PRO} $${MARKDOWN_VIEW_PRO} hunspell
