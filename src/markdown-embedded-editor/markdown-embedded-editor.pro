
TARGET = markdown-embedded-editor
TEMPLATE = lib
VERSION = 1.0.0

include(../global.pri)

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

qtHaveModule(webkitwidgets) {
    QT += webkitwidgets
    DEFINES += WITH_QTWEBENGINE=0
} else: qtHaveModule(webenginewidgets) {
    QT += webenginewidgets webchannel
    DEFINES += WITH_QTWEBENGINE=1
} else {
    message(Neither QtWebEngine nor QtWebEngine found!)
}

DEFINES += BUILDING_MARKDOWN_EMBEDDED_EDITOR_SHARED_LIB

# 头文件
HEADERS += $$files(*.h, true)

# 源文件
SOURCES += $$files(*.cpp, true)

# ui 文件
FORMS += $$files(*.ui, true)

# 资源文件
RESOURCES += $$files(*.qrc, true)

# markdown-textedit
INCLUDEPATH += $$PWD/../../3rdparty/markdown-textedit.git/src/markdown-textedit
LIBS += -L$$OUT_PWD/../../3rdparty/markdown-textedit.git/src/markdown-textedit$${OUT_TAIL}
win32: LIBS += -lmarkdown-textedit1
else: LIBS += -lmarkdown-textedit

# markdown-viewer
INCLUDEPATH += $$PWD/../../3rdparty/markdown-viewer.git/src/markdown-viewer
LIBS += -L$$OUT_PWD/../../3rdparty/markdown-viewer.git/src/markdown-viewer$${OUT_TAIL}
win32: LIBS += -lmarkdown-viewer1
else: LIBS += -lmarkdown-viewer

# jsonconfig
INCLUDEPATH += $$PWD/../../../3rdparty/jsonconfig
