
TARGET = markdown-editor
TEMPLATE = lib
VERSION = 1.0.0

include(../../global.pri)

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
}

# FIXME 从 Qt5.6 开始， QWebKit 不再被默认支持，改为使用 QtWebEngine
#       但是 Windows 下到 Qt5.7 为止，Mingw 尚不支持 QtWebEngine
lessThan(QT_VERSION, 5.6) {
    QT += webkitwidgets
} else {
    win32 {
        message(QtWebEngine not supported yet for mingw in Windows!)
    } else {
        QT += webenginewidgets webchannel
    }
}

DEFINES += BUILDING_MARKDOWN_EDITOR_DLL

# 头文件
HEADERS += $$files(*.h, true)

# 源文件
SOURCES += $$files(*.cpp, true)

# ui 文件
FORMS += $$files(*.ui, true)

# 资源文件
RESOURCES += $$files(*.qrc, true)

# markdown-textedit
INCLUDEPATH += $$PWD/..
LIBS += -L$$OUT_PWD/../markdown-textedit$${OUT_TAIL}
win32: LIBS += -lmarkdown-textedit1
else: LIBS += -lmarkdown-textedit

# markdown-viewer
LIBS += -L$$OUT_PWD/../markdown-viewer$${OUT_TAIL}
win32: LIBS += -lmarkdown-viewer1
else: LIBS += -lmarkdown-viewer

# jsonconfig
INCLUDEPATH += $$PWD/../../../3rdparty/jsonconfig

# nut
INCLUDEPATH += $$PWD/../../../3rdparty/nut.git/src
LIBS += -L$$OUT_PWD/../../../3rdparty/nut.git/proj/qtcreator/pro/nut$${OUT_TAIL}
win32: LIBS += -lnut1
else: LIBS += -lnut
