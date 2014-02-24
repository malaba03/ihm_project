#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dragwidget.h"
#include "graphicsscene.h"
#include "newprojectdialog.h"
#include "exportingasxmldialog.h"

#include <QMainWindow>
#include <QToolBar>
#include <QGraphicsView>
#include <QTreeView>
#include <QAction>
#include <QMenu>
#include <QHBoxLayout>
#include <QSplitter>
#include <QDir>
#include <QDebug>


class Mainwindow : public QMainWindow
{
    Q_OBJECT
public:
     Mainwindow();
    
     QDir getCurrentProDir() const;
     void setCurrentProDir(const QDir &value);

     QString getLayerFilPath() const;
     void setLayerFilPath(const QString &value);


public slots:
    void newProjectDialog();
    void exportAsXmlDialog();
    void openProjectPopup();
    void closeProjectPopup();
    void saveProjectPopup();
    void exitPopup();
    void receiveCurrentProjectDir(QDir currentProjectDir);
    void receiveLayerFilePath(QString layerFilePath);
    void message();
    void loadLayer();


private:

    void createMenu();
    void createActionsMenubar();

    void createToolbar();
    void createActionsToolbar();

    void createMapEditView();
    void createComponentsView();
    void setEditViewLayer();

    void createAllPopupDialog();

    DragWidget *componentsView;

    GraphicsScene *mapEditScene;
    QGraphicsView *mapEditView;

    QTreeView *projectView;

///////////////////////MENU BAR///////////////////////////
    QMenu *fileMenu;

    QAction *newProject;
    QAction *openProject;
    QAction *closeProject;
    QAction *exportAsXml;
    QAction *save;
    QAction *exit;

    QMenu *editMenu;
    QMenu *viewMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;

    ///////////////////////////////TOOL BAR//////////////////////////////
    QToolBar *toolBar;

    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *exportAct;
    QAction *copyAct;
    QAction *cutAct;
    QAction *pasteAct;
    QAction *delAct;

    QAction *openn;
    QAction *saven;
    QAction *saveas;
    QAction *importlayer;
    QAction *exporttoXml;
    QAction *cutn;
    QAction *copyn;
    QAction *pasten;
    QAction *deleten;
    QAction *aboutn;

    /////////////////////////SPECIAL FOR LAYOUT/////////////////////////////
    QHBoxLayout *layout;
    QWidget *widget;
    QSplitter *splitter;

    QTabWidget *projectViewTab;
    QTabWidget *layerViewTab;
    QTabWidget *componentsViewTab;

    ///////////////////////////DIALOG/////////////////////
    NewProjectDialog *newProjectDial;
    ExportingAsXmlDialog *exportAsXMLDial;

    //////////////////////////////PROJECT//////////////////////////
    QDir currentProDir;
    QString layerFilPath;
};

#endif // MAINWINDOW_H
