#include "Mainwindow.h"
#include "graphicsscene.h"
#include "editingview.h"

#include <QRect>
#include <QGraphicsItem>
#include <QMenuBar>
#include <QScrollArea>
#include <QKeySequence>
#include <QDir>


Mainwindow::Mainwindow()/*  :
   QMainWindow(parent),
   ui(new Ui::MainWindow)*/
{	
    //ui->setupUi(this);
    createAllPopupDialog();
    createActionsToolbar();
    createToolbar();

    createActionsMenubar();
    createMenu();

    createComponentsView();
    createMapEditView();

    setWindowTitle(tr("MapEditor"));
    connect(delAct, SIGNAL(triggered()), mapEditScene, SLOT(deleteComponents()));

}


void Mainwindow::createActionsMenubar()
{

    newProject = new QAction(tr("&New Project"),this);
    newProject->setShortcuts(QKeySequence::New);
    newProject->setStatusTip(tr("Create a new project"));
    connect(newProject, SIGNAL(triggered()), this, SLOT(newProjectDialog()));

    openProject = new QAction(tr("&Open Project"),this);
    openProject->setShortcuts(QKeySequence::Open);
    openProject->setStatusTip(tr("Open an existing project"));
    connect(openProject, SIGNAL(triggered()), this, SLOT(openProjectPopup()));

    closeProject = new QAction(tr("&Close Project"),this);
    //closeProject->setShortcuts();
    closeProject->setStatusTip(tr("Close the current project"));
    connect(closeProject, SIGNAL(triggered()), this, SLOT(closeProjectPopup()));

}

void Mainwindow::createMenu(){

    fileMenu = this->menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newProject);

    editMenu = this->menuBar()->addMenu(tr("&Edit"));
    viewMenu = this->menuBar()->addMenu(tr("&View"));
    optionMenu = this->menuBar()->addMenu(tr("&Option"));
    helpMenu = this->menuBar()->addMenu(tr("&Help"));
}


//Utilisation de label
void Mainwindow::createComponentsView(){
    projectView =new QTreeView;
    projectView->setEnabled(false);

    componentsView = new DragWidget;
    componentsView->setEnabled(false);

    //mapEditView2->setMaximumWidth(200);

}


void Mainwindow::createMapEditView()
{

    mapEditScene = new GraphicsScene(":/images/firstlayer.png");
    mapEditView = new EditingView(mapEditScene);
    mapEditView->setEnabled(false);
    mapEditView->setDragMode(QGraphicsView::RubberBandDrag);

    
    mapEditView->show();

    layout = new QHBoxLayout;
    widget = new QWidget;
    widget->setLayout(layout);

    splitter= new QSplitter(this);

    tabWidget1= new QTabWidget;
    tabWidget2= new QTabWidget;
    tabWidget3= new QTabWidget;

    tabWidget1->addTab(projectView,"Project Viewer");

    splitter->addWidget(tabWidget1);

    tabWidget2->addTab(mapEditView,"Editing of maps");

    splitter->addWidget(tabWidget2);

    layout->addWidget(splitter,8);

   QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidget(componentsView);

    tabWidget3->addTab(scrollArea,"Components Tools");
    layout->addWidget(tabWidget3,2);
    setCentralWidget(widget);

}

void Mainwindow::createToolbar()
{
    toolBar = new QToolBar(tr("File"),this);
    toolBar->addAction(newAct);

    toolBar->addAction(openAct);

    toolBar->addAction(saveAct);

    toolBar->addAction(exportAct);

    toolBar->addAction(copyAct);

    toolBar->addAction(cutAct);

    toolBar->addAction(pasteAct);

    toolBar->addAction(delAct);

    toolBar->insertSeparator(saveAct);

    toolBar->insertSeparator(delAct);

    toolBar->insertSeparator(copyAct);
    this->addToolBar(toolBar);
}

void Mainwindow::createActionsToolbar()
{
    newAct = new QAction(QString("New"),this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newProjectDialog()));

    openAct = new QAction(QString("Open"),this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    //connect(openAct, SIGNAL(triggered()), this, SLOT(open()));


    saveAct = new QAction(QString("Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    //connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    exportAct = new QAction(QString("Export As XML"),this);
    //editAct->setShortcuts(QKeySequence::New);
    exportAct->setStatusTip(tr("Edit a Task"));
    connect( exportAct, SIGNAL(triggered()), this, SLOT(exportAsXmlDialog()));

    copyAct = new QAction(QString("Copy"),this);
    //connect(consultAct, SIGNAL(triggered()), this, SLOT(consult()));

    cutAct = new QAction(QString("Cut"),this);
    //connect(addAct, SIGNAL(triggered()), this, SLOT(add()));

    pasteAct = new QAction(QString("Paste"),this);

    delAct = new QAction(QString("Delete"),this);



}

void Mainwindow::createAllPopupDialog(){

    newProjectDial = new NewProjectDialog;
    connect(newProjectDial, SIGNAL(sendCurrentProjectDir(QDir)), this, SLOT(receiveCurrentProjectDir(QDir)));
    connect(newProjectDial, SIGNAL(sendLayerFilePath(QString)), this, SLOT(receiveLayerFilePath(QString)));

    exportAsXMLDial = new ExportingAsXmlDialog;

}
 
void Mainwindow::newProjectDialog(){

    //newProjectDial->getDefautfLocationOfProjectLineEdit()->setText(QDir::homePath());
    newProjectDial->showNormal();

}

void Mainwindow::exportAsXmlDialog(){
    exportAsXMLDial->showNormal();
}

void Mainwindow::receiveCurrentProjectDir(QDir currentProjectDir){

    this->setCurrentProDir(currentProjectDir);
    qDebug() << "Current project path : " + this->currentProDir.absolutePath()+"\n";

}

void Mainwindow::receiveLayerFilePath(QString layerFilePath){

    this->setLayerFilPath(layerFilePath);
    mapEditScene->setLayerFile(layerFilPath);

    projectView->setEnabled(true);
    mapEditView->setEnabled(true);
    componentsView->setEnabled(true);

    qDebug() << "Layer file path : " + this->layerFilPath;

}

void Mainwindow::setEditViewLayer(){}
void Mainwindow::openProjectPopup(){}
void Mainwindow::closeProjectPopup(){}
void Mainwindow::saveProjectPopup(){}
void Mainwindow::exitPopup(){}

QString Mainwindow::getLayerFilPath() const
{
    return layerFilPath;
}

void Mainwindow::setLayerFilPath(const QString &value)
{
    layerFilPath = value;
}

QDir Mainwindow::getCurrentProDir() const
{
    return currentProDir;
}

void Mainwindow::setCurrentProDir(const QDir &value)
{
    currentProDir = value;
}
