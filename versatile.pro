#-------------------------------------------------
#
# Project created by QtCreator 2016-11-15T21:53:05
#
#-------------------------------------------------

QT       += core gui network webenginewidgets
CONFIG += debug
#QMAKE_CXX += distcc g++

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = versatile
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    httphelper.cpp \
    mdichild.cpp \
    exchange/exchange_helper.cpp \
    exchange/exchange_sub_win.cpp \
    sm/sm2.cpp \
    sm/smwindow.cpp \
    sm/smobj.cpp \
    sm/smproject.cpp \
    sm/treemodel.cpp \
    sm/treeitem.cpp

HEADERS  += mainwindow.h \
    httphelper.h \
    mdichild.h \
    exchange/exchange_helper.h \
    exchange/exchange_sub_win.h \
    sm/smwindow.h \
    sm/smproject.h \
    sm/treemodel.h \
    sm/treeitem.h

FORMS    += mainwindow.ui
