
TARGET = markdown-editor
TEMPLATE = app
VERSION = 0.0.1

include(../global.pri)

QT += core gui
greaterThan(QT_MAJOR_VERSION,4) {
    QT += widgets
}

# 头文件
HEADERS += $$files(*.h*, true)

# 源文件
SOURCES += $$files(*.c*, true)
