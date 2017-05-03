
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

# ͷ�ļ�
HEADERS += $$files(*.h*, true)

# Դ�ļ�
SOURCES += $$files(*.c*, true)

# ui �ļ�
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

# jsonconfig
INCLUDEPATH += $$PWD/../../3rdparty/jsonconfig
