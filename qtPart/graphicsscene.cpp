#include "graphicsscene.h"
#include <iostream>
#include <QMimeData>
#include <QLabel>
#include <QMessageBox>
#include <QImage>
#include <QString>
#include <stdio.h>
#include <stdlib.h>

#define ClassroomType ('C'+'R')


using namespace std;

GraphicsScene::GraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{

    QImage layer(":/images/bat14_level2.jpg");
    setSceneRect(QRectF(0, 0, layer.width(),layer.height()));


}

void GraphicsScene::dragEnterEvent ( QGraphicsSceneDragDropEvent * event ){

    std::cout << "in";
    if(this->sceneRect().contains(event->scenePos())){

        event->accept();

    }else {

        event->ignore();

    }

}
void GraphicsScene::dragLeaveEvent ( QGraphicsSceneDragDropEvent * event ){

    std::cout << "out";
    QGraphicsScene::dragLeaveEvent(event);

    event->accept();

}

void GraphicsScene::dragMoveEvent ( QGraphicsSceneDragDropEvent * event ){

    std::cout << "move";
    event->accept();

}

void GraphicsScene::dropEvent ( QGraphicsSceneDragDropEvent * event ){

    if ((event->mimeData()->hasFormat("application/x-dnditemdata")) && (this->sceneRect().contains(event->scenePos()) == true)) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);


        QPixmap pixmap;
        QPoint offset;
        int type;
        dataStream >> pixmap >> offset >> type;

        std::cout << type;
        printf("\nType :%d",type);

        //Peut etre utilisé pour la création des classes coeur(Classroom,Door,Corridor...)
        switch(type){

            case ClassroomType :
            tempGraphicComponent = new GraphicClassroomComponent(pixmap,type);
            tempGraphicComponent->setPos(event->scenePos());;
            break;

            default:
            tempGraphicComponent = new GraphicComponent(pixmap,type);
           //testPixmap = new GraphicComponent(pixmap);
            tempGraphicComponent->setPos(event->scenePos());;

        }

        addItem(tempGraphicComponent);
        event->accept();

    } else {

        event->ignore();
        QMessageBox msgBox;
        msgBox.setWindowTitle("Drop components issues");
        msgBox.setText("This component can't be received by the editing view.");
        msgBox.setInformativeText("We advice you to choose another one and try again.");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.exec();
    }


}

void GraphicsScene::drawBackground ( QPainter * painter, const QRectF & rect ){

    painter->setPen(Qt::black);
    painter->setBackgroundMode(Qt::OpaqueMode);
    painter->drawPixmap(QPoint(0,0),QPixmap(":/images/bat14_level2.jpg"));

}

void GraphicsScene::deleteComponents(){

    QList<QGraphicsItem*> *itemsSelected = new QList<QGraphicsItem*>();
    *itemsSelected = this->selectedItems();

    //Boucle pour la suppression de tous les éléments de la liste
    if(!(itemsSelected->isEmpty())){

            this->removeItem(itemsSelected->first());


        QMessageBox msgBox;
        msgBox.setWindowTitle("Delete results");
        msgBox.setText("The selected component had been removed of editing view.");
        //msgBox.setInformativeText("We advice you to choose another one and try again.");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.exec();


    }else {

        QMessageBox msgBox;
        msgBox.setWindowTitle("Delete results");
        msgBox.setText("Nothing to remove.");
        msgBox.setInformativeText("Please select a item and try again.");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.exec();

    }

}
