
TARGET = markdown-editor
TEMPLATE = app
VERSION = 0.0.1

include(../global.pri)

QT += core gui printsupport
greaterThan(QT_MAJOR_VERSION,4): QT += widgets
win32: QT += winextras

qtHaveModule(webkitwidgets) {
    QT += webkitwidgets
    DEFINES += WITH_QTWEBENGINE=0
} else: qtHaveModule(webenginewidgets) {
    QT += webenginewidgets webchannel
    DEFINES += WITH_QTWEBENGINE=1
} else {
    message(Neither QtWebEngine nor QtWebEngine found!)
}

# 头文件
HEADERS += $$files(*.h*, true)

# 源文件
SOURCES += \
    $$files(*.c*) \
    $$files(theme/*.c*, true) \
    $$files(spellchecker/*.c*, true) \
    $$files(snippets/*.c*, true) \
    hunspell/spellchecker.cpp

macx {
    SOURCES += \
        hunspell/spellchecker_macx.cpp
} else:win32 {
    SOURCES += \
        hunspell/spellchecker_win.cpp
} else {
    SOURCES += \
        hunspell/spellchecker_unix.cpp
}

SOURCES += \
    $$files(controls/*.c*, true)

# ui 文件
FORMS += $$files(*.ui, true)

# 资源文件
RESOURCES += $$files(*.qrc, true)

# 翻译
TRANSLATIONS += \
    translations/cutemarked_cs.ts \
    translations/cutemarked_da.ts \
    translations/cutemarked_de.ts \
    translations/cutemarked_el.ts \
    translations/cutemarked_es.ts \
    translations/cutemarked_fr.ts \
    translations/cutemarked_hu_HU.ts \
    translations/cutemarked_id.ts \
    translations/cutemarked_ja.ts \
    translations/cutemarked_pl.ts \
    translations/cutemarked_pt_BR.ts \
    translations/cutemarked_ru.ts \
    translations/cutemarked_zh_CN.ts

# translations
lrelease.input         = TRANSLATIONS
lrelease.output        = ${QMAKE_FILE_PATH}/${QMAKE_FILE_BASE}.qm
lrelease.commands      = $$[QT_INSTALL_BINS]/lrelease ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_PATH}/${QMAKE_FILE_BASE}.qm
lrelease.CONFIG       += no_link target_predeps
QMAKE_EXTRA_COMPILERS += lrelease

# markdown-textedit
INCLUDEPATH += $$PWD/../../3rdparty/markdown-textedit.git/src/markdown-textedit
LIBS += -L$$OUT_PWD/../../3rdparty/markdown-textedit.git/src/markdown-textedit$${OUT_TAIL}
win32: LIBS += -lmarkdown-textedit1
else: LIBS += -lmarkdown-textedit

# markdown-view
INCLUDEPATH += $$PWD/../../3rdparty/markdown-view.git/src/markdown-view
LIBS += -L$$OUT_PWD/../../3rdparty/markdown-view.git/src/markdown-view$${OUT_TAIL}
win32: LIBS += -lmarkdown-view1
else: LIBS += -lmarkdown-view

# hunspell
INCLUDEPATH += $$PWD/../../3rdparty/hunspell.git/src
LIBS += -L$$OUT_PWD/../hunspell$${OUT_TAIL} -lhunspell

# jsonconfig
INCLUDEPATH += $$PWD/../../3rdparty/jsonconfig

################################################################################

mac {
    MARKDOWN_EDITOR_LIBS = \
        $$OUT_PWD/../../3rdparty/markdown-textedit.git/src/markdown-textedit/libmarkdown-textedit.1.dylib \
        $$OUT_PWD/../../3rdparty/markdown-view.git/src/markdown-view/libmarkdown-view.1.dylib \
        $$OUT_PWD/../hunspell/libhunspell.dylib
} else:win32 {
    MARKDOWN_EDITOR_LIBS = \
        $$OUT_PWD/../../3rdparty/markdown-textedit.git/src/markdown-textedit/$${DEBUG_MODE}/markdown-textedit1.dll \
        $$OUT_PWD/../../3rdparty/markdown-view.git/src/markdown-view/$${DEBUG_MODE}/markdown-view1.dll \
        $$OUT_PWD/../hunspell/$${DEBUG_MODE}/hunspell.dll
} else {
    MARKDOWN_EDITOR_LIBS = \
        $$OUT_PWD/../../3rdparty/markdown-textedit.git/src/markdown-textedit/libmarkdown-textedit.1.so \
        $$OUT_PWD/../../3rdparty/markdown-view.git/src/markdown-view/libmarkdown-view.1.so \
        $$OUT_PWD/../hunspell/libhunspell.so
}

include(post_link.pri)

include(archive.pri)
