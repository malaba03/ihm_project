#include <QLabel>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>
#include <QPainter>
#include <QVBoxLayout>
#include "dragwidget.h"
#include "componentlabel.h"

 DragWidget::DragWidget(QWidget *parent)
     : QFrame(parent)
 {
     //setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
     //setAcceptDrops(true);

     int keyCorridor('C');
     int keyClassroom('C'+'R');
     int keyDoor('D');
     int keyStair('S');
     int keyElevator('E');
     int keyRestroom('R');
     int keyQrCode('Q');

    QVBoxLayout *ComponentIconLayout = new QVBoxLayout;


    ComponentIconLayout->addWidget(new QLabel("Corridors"));

    //The name of each label variable correspond to the sens and position of the component

    QLabel *corridorVIc = new ComponentLabel(this,":/images/corridors/corridorV.png",keyCorridor);
    QLabel *corridorHIc = new ComponentLabel(this,":/images/corridors/corridorH.png",keyCorridor);

    ComponentIconLayout->addWidget(corridorVIc);
    ComponentIconLayout->addWidget(corridorHIc);

    ComponentIconLayout->addWidget(new QLabel("Classrooms"));

    QLabel *classroomIc = new ComponentLabel(this,":/images/classrooms/classroom",keyClassroom);

    ComponentIconLayout->addWidget(classroomIc);

    ComponentIconLayout->addWidget(new QLabel("Doors"));

    QLabel *doorDLVIc = new ComponentLabel(this,":/images/doors/toDownL1.png", keyDoor);
    QLabel *doorDRVIc = new ComponentLabel(this,":/images/doors/toDownR1.png", keyDoor);
    QLabel *doorULVIc = new ComponentLabel(this,":/images/doors/toUpR1.png", keyDoor);
    QLabel *doorURVIc = new ComponentLabel(this,":/images/doors/toUpL1.png", keyDoor);

    QLabel *doorLLHIc = new ComponentLabel(this,":/images/doors/toLeftL1.png", keyDoor);
    QLabel *doorLRHIc = new ComponentLabel(this,":/images/doors/toLeftR1.png", keyDoor);
    QLabel *doorRLHIc = new ComponentLabel(this,":/images/doors/toRightL1.png", keyDoor);
    QLabel *doorRRHIc = new ComponentLabel(this,":/images/doors/toRightR1.png", keyDoor);

    ComponentIconLayout->addWidget(doorDLVIc);
    ComponentIconLayout->addWidget(doorDRVIc);
    ComponentIconLayout->addWidget(doorULVIc);
    ComponentIconLayout->addWidget(doorURVIc);

    ComponentIconLayout->addWidget(doorLLHIc);
    ComponentIconLayout->addWidget(doorLRHIc);
    ComponentIconLayout->addWidget(doorRLHIc);
    ComponentIconLayout->addWidget(doorRRHIc);


    ComponentIconLayout->addWidget(new QLabel("Stairs"));

    //Missing porte sous-sol
    QLabel *stairDIc = new ComponentLabel(this,":/images/stairs/stair1.png", keyStair);
    QLabel *stairUIc = new ComponentLabel(this,":/images/stairs/stair2.png", keyStair);

    QLabel *stairDVIc = new ComponentLabel(this,":/images/stairs/toDown.png", keyStair);
    QLabel *stairUVIc = new ComponentLabel(this,":/images/stairs/toUp.png", keyStair);


    QLabel *stairLHIc = new ComponentLabel(this,":/images/stairs/toLeft.png", keyStair);
    QLabel *stairRHIc = new ComponentLabel(this,":/images/stairs/toRight.png", keyStair);

    ComponentIconLayout->addWidget(stairDIc);
    ComponentIconLayout->addWidget(stairUIc);
    ComponentIconLayout->addWidget(stairDVIc);
    ComponentIconLayout->addWidget(stairUVIc);
    ComponentIconLayout->addWidget(stairLHIc);
    ComponentIconLayout->addWidget(stairRHIc);


    ComponentIconLayout->addWidget(new QLabel("Elevator"));

    QLabel *elevatorIc = new ComponentLabel(this,":/images/elevators/elevator.png",keyElevator);
    ComponentIconLayout->addWidget(elevatorIc);


    ComponentIconLayout->addWidget(new QLabel("Restrooms"));

    QLabel * restroomIc = new ComponentLabel(this,":/images/restrooms/restroom.png",keyRestroom);

    ComponentIconLayout->addWidget(restroomIc);



    ComponentIconLayout->addWidget(new QLabel("QrCodeBorn"));

    QLabel * qrCodeIc = new ComponentLabel(this,":/images/qrCode/qrcode.png",keyQrCode);
    ComponentIconLayout->addWidget(qrCodeIc);



    this->setLayout(ComponentIconLayout);

 }

 void DragWidget::dragEnterEvent(QDragEnterEvent *event)
 {
     if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
         if (event->source() == this) {
             event->setDropAction(Qt::MoveAction);
             event->accept();
         } else {
             event->acceptProposedAction();
         }
     } else {
         event->ignore();
     }
 }

 void DragWidget::dragMoveEvent(QDragMoveEvent *event)
 {
     if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
         if (event->source() == this) {
             event->setDropAction(Qt::MoveAction);
             event->accept();
         } else {
             event->acceptProposedAction();
         }
     } else {
         event->ignore();
     }
 }

 void DragWidget::dropEvent(QDropEvent *event)
 {
     if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
         QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
         QDataStream dataStream(&itemData, QIODevice::ReadOnly);

         QPixmap pixmap;
         QPoint offset;
         dataStream >> pixmap >> offset;

      QLabel *newIcon = new QLabel(this);
         newIcon->setPixmap(pixmap);
         newIcon->move(event->pos() - offset);
         newIcon->show();
         newIcon->setAttribute(Qt::WA_DeleteOnClose);

         if (event->source() == this) {
             event->setDropAction(Qt::MoveAction);
             event->accept();
         } else {
             event->acceptProposedAction();
         }
     } else {
         event->ignore();
     }
 }

 void DragWidget::mousePressEvent(QMouseEvent *event)
 {
     ComponentLabel *child = static_cast<ComponentLabel*>(childAt(event->pos()));
     if (!child)
         return;

     QPixmap pixmap = *child->pixmap();

     int type = child->getType();

     QByteArray itemData;
     QDataStream dataStream(&itemData, QIODevice::WriteOnly);
     dataStream << pixmap << QPoint(event->pos() - child->pos()) << type;

     //Permit to dragged object to be recognize by view when it'll be drop
     QMimeData *mimeData = new QMimeData;
     mimeData->setData("application/x-dnditemdata", itemData);

     QDrag *drag = new QDrag(this);
     drag->setMimeData(mimeData);
     drag->setPixmap(pixmap);

     //Show the label during the drag
     drag->setHotSpot(event->pos() - child->pos());


    QPixmap tempPixmap = pixmap;
     QPainter painter;
     painter.begin(&tempPixmap);
     painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
     painter.end();

     child->setPixmap(tempPixmap);

     if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)
         child->close();
     else {
         child->show();

    child->setPixmap(pixmap);
     }
 }
