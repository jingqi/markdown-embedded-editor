
TARGET = markdown-editor
TEMPLATE = app
VERSION = 0.0.1

include(../global.pri)

QT += core gui
greaterThan(QT_MAJOR_VERSION,4) {
    QT += widgets
}

# ͷ�ļ�
HEADERS += $$files(*.h*, true)

# Դ�ļ�
SOURCES += $$files(*.c*, true)
