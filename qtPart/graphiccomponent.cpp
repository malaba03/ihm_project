#include "graphiccomponent.h"
#include <iostream>
#include <QDebug>
#include <QGraphicsPixmapItem>

#include "math.h"

GraphicComponent::GraphicComponent(QPixmap pM,int type):
    TopGraphicComponent(pM,type)
{
    _text.setPlainText("Double click \non classroom to edit \nhis name");
    _text.setParentItem(this);
    _text.setFlag(QGraphicsItem::ItemIsSelectable,true);
    _text.setFlag(QGraphicsItem::ItemIsMovable);
    _text.setFlag(QGraphicsItem::ItemIsFocusable);
    changeClassroomNameDialog = new PopUp;
    connect(changeClassroomNameDialog, SIGNAL(sendNewClassroomName(QString)), this, SLOT(setClassroomName(QString)));
}

GraphicComponent::~GraphicComponent()
{
    free(changeClassroomNameDialog);
}

void GraphicComponent::setClassroomName(QString newClassroomName){

    qDebug() << "New text:"+newClassroomName;
    this->_text.setPlainText(newClassroomName);

}

void GraphicComponent::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event ){

    event->accept();
    changeClassroomNameDialog->getTextEdit()->setText(_text.toPlainText());
    changeClassroomNameDialog->showNormal();

}

