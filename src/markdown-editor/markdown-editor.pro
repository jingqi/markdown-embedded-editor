
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
