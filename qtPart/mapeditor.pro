QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mapeditor
TEMPLATE = app

HEADERS += Mainwindow.h \
    editingview.h \
    graphicsscene.h \
    dragwidget.h \
    componentlabel.h \
    graphiccomponent.h \
    cornergrabber.h \
    graphicclassroomcomponent.h\
    popup.h \
    newprojectdialog.h \
    exportingasxmldialog.h

SOURCES += Mainwindow.cpp main.cpp \
    editingview.cpp \
    graphicsscene.cpp \
    dragwidget.cpp \
    componentlabel.cpp \
    graphiccomponent.cpp \
    cornergrabber.cpp \
    graphicclassroomcomponent.cpp\
    popup.cpp \
    newprojectdialog.cpp \
    exportingasxmldialog.cpp

RESOURCES += \
    components.qrc

FORMS += \
    mainwindow.ui \
    newprojectdialog.ui \
    exportingasxmldialog.ui



