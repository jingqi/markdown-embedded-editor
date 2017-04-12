
TEMPLATE = subdirs

SUBDIRS += \
    markdown-embedded-editor \
    test-markdown-embedded-editor

test-markdown-embedded-editor.depends = markdown-embedded-editor
