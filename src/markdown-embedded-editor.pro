
TEMPLATE = subdirs

MARKDOWN_TEXTEDIT_PRO = ../3rdparty/markdown-textedit.git/src/markdown-textedit.pro
MARKDOWN_VIEWER_PRO = ../3rdparty/markdown-viewer.git/src/markdown-viewer.pro

SUBDIRS += \
    $${MARKDOWN_TEXTEDIT_PRO} \
    $${MARKDOWN_VIEWER_PRO} \
    markdown-embedded-editor \
    test-markdown-embedded-editor

markdown-embedded-editor.depends = $${MARKDOWN_TEXTEDIT_PRO} $${MARKDOWN_VIEWER_PRO}
test-markdown-embedded-editor.depends = markdown-embedded-editor
