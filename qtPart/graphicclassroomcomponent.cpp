#include "graphicclassroomcomponent.h"
#include <iostream>
#include <QDebug>
#include <QGraphicsPixmapItem>

#include "math.h"

GraphicClassroomComponent::GraphicClassroomComponent(QPixmap pM,int type):
    GraphicComponent(pM,type)
{
    _text.setPlainText("Double click \non classroom to edit \nhis name");
    _text.setParentItem(this);
    _text.setFlag(QGraphicsItem::ItemIsSelectable,true);
    _text.setFlag(QGraphicsItem::ItemIsMovable);
    _text.setFlag(QGraphicsItem::ItemIsFocusable);
    changeClassroomNameDialog = new PopUp;
    connect(changeClassroomNameDialog, SIGNAL(sendNewClassroomName(QString)), this, SLOT(setClassroomName(QString)));
}

GraphicClassroomComponent::~GraphicClassroomComponent()
{
    free(changeClassroomNameDialog);
}

void GraphicClassroomComponent::setClassroomName(QString newClassroomName){

    qDebug() << "New text:"+newClassroomName;
    this->_text.setPlainText(newClassroomName);

}

void GraphicClassroomComponent::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event ){

    event->accept();
    changeClassroomNameDialog->getTextEdit()->setText(_text.toPlainText());
    changeClassroomNameDialog->showNormal();

}

