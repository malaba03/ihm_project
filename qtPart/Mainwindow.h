#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QGraphicsView>
#include <QTreeView>
#include <QAction>
#include <QMenu>
#include <QHBoxLayout>
#include <QSplitter>
#include "dragwidget.h"
#include "graphicsscene.h"

/*namespace Ui {
class MainWindow;
}*/

class Mainwindow : public QMainWindow
{
    Q_OBJECT
public:
     Mainwindow();
    
public slots:
    void newProjectPopup();
    void openProjectPopup();
    void closeProjectPopup();
    void exportPopup();
    void saveProjectPopup();
    void exitPopup();


private:

    //Ui::MainWindow *ui;
    void createMenu();
    void createActionsMenubar();

    void createToolbar();
    void createActionsToolbar();

    void createMapEditView();
    void createComponentsView();
    void createComponentsView2();
    void setEditViewLayer();

    DragWidget *componentsView;

    GraphicsScene *mapEditScene;
    QGraphicsView *mapEditView;

    QTreeView *projectView;

///////////////////////Menu bar///////////////////////////
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

    ///////////////////////////////Tool bar//////////////////////////////
    QToolBar *toolBar;

    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *exportAct;
    QAction *copyAct;
    QAction *cutAct;
    QAction *pasteAct;
    QAction *delAct;

    /////////////////////////SPECIAL FOR LAYOUT/////////////////////////////
    QHBoxLayout *layout;
    QWidget *widget;
    QSplitter *splitter;

    QTabWidget *tabWidget1;
    QTabWidget *tabWidget2;
    QTabWidget *tabWidget3;
};

#endif // MAINWINDOW_H
