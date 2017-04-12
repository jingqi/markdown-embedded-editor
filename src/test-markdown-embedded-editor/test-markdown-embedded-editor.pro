
TARGET = test-markdown-embedded-editor
TEMPLATE = app

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

# 头文件
HEADERS += $$files(*.h*, true)

# 源文件
SOURCES += $$files(*.c*, true)

# ui 文件
FORMS += $$files(*.ui, true)

# 资源文件
RESOURCES += $$files(*.qrc, true)

# 其他文件
OTHER_FILES += test.md

# markdown-embedded-editor
INCLUDEPATH += $$PWD/../markdown-embedded-editor
LIBS += -L$$OUT_PWD/../markdown-embedded-editor$${OUT_TAIL}
win32: LIBS += -lmarkdown-embedded-editor1
else: LIBS += -lmarkdown-embedded-editor

# markdown-viewer
INCLUDEPATH += $$PWD/../../3rdparty/markdown-viewer.git/src/markdown-viewer

# 资源打包
mac {
    libs.path = Contents/Frameworks
    libs.files = \
        $$OUT_PWD/../../3rdparty/markdown-textedit.git/src/markdown-textedit/libmarkdown-textedit.1.dylib \
        $$OUT_PWD/../../3rdparty/markdown-viewer.git/src/discount/libdiscount.1.dylib \
        $$OUT_PWD/../../3rdparty/markdown-viewer.git/src/hoedown/libhoedown.1.dylib \
        $$OUT_PWD/../../3rdparty/markdown-viewer.git/src/markdown-viewer/libmarkdown-viewer.1.dylib \
        $$OUT_PWD/../markdown-embedded-editor/libmarkdown-embedded-editor.1.dylib
    QMAKE_BUNDLE_DATA += libs
} else: win32 {
    # 拷贝资源文件
    DST = $$OUT_PWD/$${DEBUG_MODE}
    DST ~= s,/,\\,g

    SRC = $$OUT_PWD/../../3rdparty/markdown-textedit.git/src/markdown-textedit/$${DEBUG_MODE}/markdown-textedit1.dll
    POST_TARGETDEPS += $${SRC}
    SRC ~= s,/,\\,
    QMAKE_POST_LINK += $$quote(cmd /c xcopy /y /i $${SRC} $${DST}$$escape_expand(\n\t))

    SRC = $$OUT_PWD/../../3rdparty/markdown-viewer.git/src/discount/$${DEBUG_MODE}/discount.dll
    POST_TARGETDEPS += $${SRC}
    SRC ~= s,/,\\,
    QMAKE_POST_LINK += $$quote(cmd /c xcopy /y /i $${SRC} $${DST}$$escape_expand(\n\t))

    SRC = $$OUT_PWD/../../3rdparty/markdown-viewer.git/src/hoedown/$${DEBUG_MODE}/hoedown.dll
    POST_TARGETDEPS += $${SRC}
    SRC ~= s,/,\\,
    QMAKE_POST_LINK += $$quote(cmd /c xcopy /y /i $${SRC} $${DST}$$escape_expand(\n\t))

    SRC = $$OUT_PWD/../../3rdparty/markdown-viewer.git/src/markdown-viewer/$${DEBUG_MODE}/markdown-viewer1.dll
    POST_TARGETDEPS += $${SRC}
    SRC ~= s,/,\\,
    QMAKE_POST_LINK += $$quote(cmd /c xcopy /y /i $${SRC} $${DST}$$escape_expand(\n\t))

    SRC = $$OUT_PWD/../markdown-embedded-editor/$${DEBUG_MODE}/markdown-embedded-editor1.dll
    POST_TARGETDEPS += $${SRC}
    SRC ~= s,/,\\,
    QMAKE_POST_LINK += $$quote(cmd /c xcopy /y /i $${SRC} $${DST}$$escape_expand(\n\t))
} else: unix {
    SRC = $$OUT_PWD/../../3rdparty/markdown-textedit.git/src/markdown-textedit/libmarkdown-textedit.1.so
    POST_TARGETDEPS += $${SRC}
    QMAKE_POST_LINK += cp -Lf $${SRC} $$OUT_PWD/ ;

    SRC = $$OUT_PWD/../../3rdparty/markdown-viewer.git/src/discount/libdiscount.1.so
    POST_TARGETDEPS += $${SRC}
    QMAKE_POST_LINK += cp -Lf $${SRC} $$OUT_PWD/ ;

    SRC = $$OUT_PWD/../../3rdparty/markdown-viewer.git/src/hoedown/libhoedown.1.so
    POST_TARGETDEPS += $${SRC}
    QMAKE_POST_LINK += cp -Lf $${SRC} $$OUT_PWD/ ;

    SRC = $$OUT_PWD/../../3rdparty/markdown-viewer.git/src/markdown-viewer/libmarkdown-viewer.1.so
    POST_TARGETDEPS += $${SRC}
    QMAKE_POST_LINK += cp -Lf $${SRC} $$OUT_PWD/ ;

    SRC = $$OUT_PWD/../markdown-embedded-editor/libmarkdown-embedded-editor.1.so
    POST_TARGETDEPS += $${SRC}
    QMAKE_POST_LINK += cp -Lf $${SRC} $$OUT_PWD/ ;
}
