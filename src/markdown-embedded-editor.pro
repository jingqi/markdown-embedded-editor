
TEMPLATE = subdirs

MARKDOWN_TEXTEDIT_PRO = ../3rdparty/markdown-textedit.git/src/markdown-textedit.pro

SUBDIRS += \
    $${MARKDOWN_TEXTEDIT_PRO} \
    markdown-embedded-editor \
    test-markdown-embedded-editor

markdown-embedded-editor.depends = $${MARKDOWN_TEXTEDIT_PRO}
test-markdown-embedded-editor.depends = markdown-embedded-editor
