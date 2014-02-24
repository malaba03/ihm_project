#include "Mainwindow.h"
#include "graphicsscene.h"

#include <QMessageBox>
#include <QRect>
#include <QGraphicsItem>
#include <QMenuBar>
#include <QScrollArea>
#include <QKeySequence>
#include <QDir>
#include <QFileDialog>


Mainwindow::Mainwindow()
{	
    this->setWindowIcon(QIcon(":/menuicon/iconesmenu/maps.png"));
    createAllPopupDialog();
    createActionsToolbar();
    createToolbar();

    createActionsMenubar();
    createMenu();

    createComponentsView();
    createMapEditView();

    setWindowTitle(tr("MapEditor"));
    connect(delAct, SIGNAL(triggered()), tempEditScene, SLOT(deleteComponents()));
    connect(deleten, SIGNAL(triggered()), tempEditScene, SLOT(deleteComponents()));
}


void Mainwindow::createActionsMenubar()
{

    newProject = new QAction(tr("&New Project"),this);
    newProject->setIcon(QIcon(":/menuicon/iconesmenu/new.png"));
    newProject->setIconVisibleInMenu(true);
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

    exit = new QAction(tr("&Exit"),this);
    closeProject->setStatusTip(tr("Close the mapEditor windows"));
    connect(exit, SIGNAL(triggered()), this, SLOT(close()));

    openn = new QAction(tr("Open Project"),this);
    openn->setIcon(QIcon(":/menuicon/iconesmenu/open.png"));
    openn->setIconVisibleInMenu(true);
    connect(openn, SIGNAL(triggered()), this, SLOT(openProjectPopup()));


    saven = new QAction(tr("Save"),this);
    saven->setIcon(QIcon(":/menuicon/iconesmenu/save.png"));
    saven->setIconVisibleInMenu(true);

    saveas = new QAction(tr("Save As"),this);

    importlayer = new QAction(tr("Import Layer"),this);
    connect(importlayer, SIGNAL(triggered()), this, SLOT(loadLayer()));

    exporttoXml= new QAction(tr("Export To XML"),this);
    exporttoXml->setIcon(QIcon(":/menuicon/iconesmenu/save.png"));
    exporttoXml->setIconVisibleInMenu(true);
    connect(exporttoXml, SIGNAL(triggered()), this, SLOT(exportAsXmlDialog()));

    exit = new QAction(tr("Exit"),this);

    cutn = new QAction(tr("Cut"),this);
    cutn->setIcon(QIcon(":/menuicon/iconesmenu/cut.png"));
    cutn->setIconVisibleInMenu(true);

    copyn = new QAction(tr("Copy"),this);
    copyn->setIcon(QIcon(":/menuicon/iconesmenu/copy.png"));
    copyn->setIconVisibleInMenu(true);

    pasten = new QAction(tr("Paste"),this);
    pasten->setIcon(QIcon(":/menuicon/iconesmenu/paste.png"));
    pasten->setIconVisibleInMenu(true);

    deleten = new QAction(tr("Delete Item"),this);
    deleten->setIcon(QIcon(":/menuicon/iconesmenu/delete.png"));
    deleten->setIconVisibleInMenu(true);


    aboutn = new QAction(tr("About Map Editor 1.1"),this);

}


void Mainwindow::createMenu(){

    fileMenu = this->menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newProject);
    fileMenu->addAction(openn);
    fileMenu->insertSeparator(saven);
    fileMenu->addAction(saven);
    fileMenu->addAction(saveas);
    fileMenu->insertSeparator(importlayer);
    fileMenu->addAction(importlayer);
    fileMenu->addAction(exporttoXml);
    fileMenu->insertSeparator(exit);
    fileMenu->addAction(exit);
    connect(exit,SIGNAL(triggered()),this,SLOT(close()));

    editMenu = this->menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutn);
    editMenu->addAction(copyn);
    editMenu->addAction(pasten);
    editMenu->addSeparator();
    editMenu->addAction(deleten);

    helpMenu = this->menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutn);
    connect(aboutn,SIGNAL(triggered()),this,SLOT(message()));
}


void Mainwindow::createComponentsView(){
    projectView =new QTreeView;
    projectView->setEnabled(false);

    componentsView = new DragWidget;
    componentsView->setEnabled(false);

}


void Mainwindow::createMapEditView()
{

    tempEditScene = new GraphicsScene(":/images/firstlayer.png");
    tempEditView = new EditingView(tempEditScene);
    tempEditView->setEnabled(false);
    tempEditView->setDragMode(QGraphicsView::RubberBandDrag);

    listGraphicsSceneView.append(tempEditScene);
    listEditingView.append(tempEditView);

    
    tempEditView->show();

    layout = new QHBoxLayout;
    widget = new QWidget;
    widget->setLayout(layout);

    splitter= new QSplitter(this);

    projectViewTab= new QTabWidget;
    layerViewTab= new QTabWidget;
    componentsViewTab= new QTabWidget;

    connect(layerViewTab, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));

    projectViewTab->addTab(projectView,"Project Viewer");

    splitter->addWidget(projectViewTab);

    layerViewTab->addTab(tempEditView,"Editing of maps");

    splitter->addWidget(layerViewTab);

    layout->addWidget(splitter,8);

   QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidget(componentsView);

    componentsViewTab->addTab(scrollArea,"Components Tools");
    layout->addWidget(componentsViewTab,2);
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
    newAct->setIcon(QIcon(":/menuicon/iconesmenu/new.png"));
    newAct->setIconVisibleInMenu(true);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newProjectDialog()));

    openAct = new QAction(QString("Open"),this);
    openAct->setIcon(QIcon(":/menuicon/iconesmenu/open.png"));
    openAct->setIconVisibleInMenu(true);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(openProjectPopup()));


    saveAct = new QAction(QString("Save"), this);
    saveAct->setIcon(QIcon(":/menuicon/iconesmenu/save.png"));
    saveAct->setIconVisibleInMenu(true);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    //connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    exportAct = new QAction(QString("Export to XML"),this);
    //editAct->setShortcuts(QKeySequence::New);
    exportAct->setIcon(QIcon(":/menuicon/iconesmenu/file_xml.png"));
    exportAct->setIconVisibleInMenu(true);
    exportAct->setStatusTip(tr("Edit a Task"));
    connect( exportAct, SIGNAL(triggered()), this, SLOT(exportAsXmlDialog()));

    copyAct = new QAction(QString("Copy"),this);
    copyAct->setIcon(QIcon(":/menuicon/iconesmenu/copy.png"));
    copyAct->setIconVisibleInMenu(true);
    //connect(consultAct, SIGNAL(triggered()), this, SLOT(consult()));

    cutAct = new QAction(QString("Cut"),this);
    cutAct->setIcon(QIcon(":/menuicon/iconesmenu/cut.png"));
    cutAct->setIconVisibleInMenu(true);
    //connect(addAct, SIGNAL(triggered()), this, SLOT(add()));

    pasteAct = new QAction(QString("Paste"),this);
    pasteAct->setIcon(QIcon(":/menuicon/iconesmenu/paste.png"));
    pasteAct->setIconVisibleInMenu(true);

    delAct = new QAction(QString("Delete"),this);
    delAct->setIcon(QIcon(":/menuicon/iconesmenu/delete.png"));
    delAct->setIconVisibleInMenu(true);

}


void Mainwindow::createAllPopupDialog(){

    newProjectDial = new NewProjectDialog;
    connect(newProjectDial, SIGNAL(sendCurrentProjectDir(QDir)), this, SLOT(receiveCurrentProjectDir(QDir)));
    connect(newProjectDial, SIGNAL(sendLayerFilePath(QString)), this, SLOT(receiveLayerFilePath(QString)));

    exportAsXMLDial = new ExportingAsXmlDialog;

}


void Mainwindow::newProjectDialog(){

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
    tempEditScene->setLayerFile(layerFilPath);

    projectView->setEnabled(true);
    tempEditView->setEnabled(true);
    componentsView->setEnabled(true);

    qDebug() << "Layer file path : " + this->layerFilPath;

}


void Mainwindow::openProjectPopup(){

    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open File"),"/");
}


void Mainwindow::loadLayer()
{
    QString pathLayer = QFileDialog::getOpenFileName(this, tr("Opening a image used as layer)"), QDir::homePath(), tr("Image Files (*.png *.jpg)"));
    GraphicsScene *tempScene = new GraphicsScene(pathLayer);
    EditingView *tempEditView = new EditingView(tempScene);
    tempEditView ->setDragMode(QGraphicsView::RubberBandDrag);
    tempEditView ->show();
    layerViewTab->addTab(tempEditView,"Editing of maps");
    layerViewTab->setTabsClosable(true);

}


void Mainwindow::closeTab(int indexTab)
{
    layerViewTab->removeTab(indexTab);
}


void Mainwindow::message()
{
    QMessageBox::information(this,"Map Info", "Auteurs : Lamine BA, Yannis GREGO, Pierre GNAGNE");
}


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


void Mainwindow::closeProjectPopup(){}
void Mainwindow::saveProjectPopup(){}
void Mainwindow::exitPopup(){}
