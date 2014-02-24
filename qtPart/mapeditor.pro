QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mapeditor
TEMPLATE = app

HEADERS += Mainwindow.h \
    editingview.h \
    graphicsscene.h \
    dragwidget.h \
    componentlabel.h \
    cornergrabber.h \
    popup.h \
    newprojectdialog.h \
    exportingasxmldialog.h \
    graphiccomponent.h \
    topgraphiccomponent.h

SOURCES += Mainwindow.cpp main.cpp \
    editingview.cpp \
    graphicsscene.cpp \
    dragwidget.cpp \
    componentlabel.cpp \
    cornergrabber.cpp \
    popup.cpp \
    newprojectdialog.cpp \
    exportingasxmldialog.cpp \
    graphiccomponent.cpp \
    topgraphiccomponent.cpp

RESOURCES += \
    components.qrc

FORMS += \
    mainwindow.ui \
    newprojectdialog.ui \
    exportingasxmldialog.ui



