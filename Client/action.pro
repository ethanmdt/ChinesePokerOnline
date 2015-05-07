#-------------------------------------------------
#
# Project created by QtCreator 2015-05-07T13:43:59
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = action
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    sockabstract.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    sockabstract.h

FORMS    += mainwindow.ui \
    dialog.ui
