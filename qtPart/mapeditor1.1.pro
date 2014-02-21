QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mapeditor1.1
TEMPLATE = app

HEADERS += Mainwindow.h \
    editingview.h \
    graphicsscene.h \
    dragwidget.h \
    componentlabel.h \
    graphiccomponent.h \
    cornergrabber.h \
    graphicclassroomcomponent.h\
    popup.h

SOURCES += Mainwindow.cpp main.cpp \
    editingview.cpp \
    graphicsscene.cpp \
    dragwidget.cpp \
    componentlabel.cpp \
    graphiccomponent.cpp \
    cornergrabber.cpp \
    graphicclassroomcomponent.cpp\
    popup.cpp

RESOURCES += \
    components.qrc

FORMS += \
    mainwindow.ui



