#include "graphiccomponent.h"
#include <iostream>
#include <QDebug>
#include <QGraphicsPixmapItem>

#include "math.h"

GraphicComponent::GraphicComponent(QPixmap pM,int type):
    _outterborderColor(Qt::black),
    _outterborderPen(),
    _location(0,0),
    _dragStart(0,0),
    _width(qreal(pM.width())*2),
    _height(qreal(pM.height())*2),
    _cornerDragStart(0,0),
    _XcornerGrabBuffer(20),
    _YcornerGrabBuffer(20),
    _drawingWidth(_width - _XcornerGrabBuffer),
    _drawingHeight(_height - _YcornerGrabBuffer),
    _drawingOrigenX(_XcornerGrabBuffer),
    _drawingOrigenY(_YcornerGrabBuffer),
    pixM(pM),
    type(type)
{
    _outterborderPen.setWidth(2);
    _outterborderPen.setColor(_outterborderColor);

    setAcceptDrops(true);
    this->setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable,true);
    setFlag(QGraphicsItem::ItemIsMovable);


}

/**
 *  To allow the user to grab the corners to re-size, we need to get a hover
 *  indication. But if the mouse pointer points to the left, then when the mouse
 *  tip is to the left but just outsize the box, we will not get the hover.
 *  So the solution is to tell the graphics scene the box is larger than
 *  what the painter actually paints in. This way when the user gets the mouse
 *  within a few pixels of what appears to be the edge of the box, we get
 *  the hover indication.

 *  So the cornerGrabBuffer is a few pixel wide buffer zone around the outside
 *  edge of the box.
 *
 */
void GraphicComponent::adjustSize(int x, int y)
{
    _width += x;
    _height += y;

    _drawingWidth =  _width - _XcornerGrabBuffer;
    _drawingHeight=  _height - _YcornerGrabBuffer;
}

/**
  * This scene event filter has been registered with all four corner grabber items.
  * When called, a pointer to the sending item is provided along with a generic
  * event.  A dynamic_cast is used to determine if the event type is one of the events
  * we are interrested in.
  */
bool GraphicComponent::sceneEventFilter ( QGraphicsItem * watched, QEvent * event )
{
    qDebug() << " QEvent == " + QString::number(event->type());

    CornerGrabber * corner = dynamic_cast<CornerGrabber *>(watched);
    if ( corner == NULL) return false; // not expected to get here

    QGraphicsSceneMouseEvent * mevent = dynamic_cast<QGraphicsSceneMouseEvent*>(event);
    if ( mevent == NULL)
    {
        // this is not one of the mouse events we are interrested in
        return false;
    }


    switch (event->type() )
    {
            // if the mouse went down, record the x,y coords of the press, record it inside the corner object
        case QEvent::GraphicsSceneMousePress:
            {
                corner->setMouseState(CornerGrabber::kMouseDown);
                corner->mouseDownX = mevent->pos().x();
                corner->mouseDownY = mevent->pos().y();
            }
            break;

        case QEvent::GraphicsSceneMouseRelease:
            {
                corner->setMouseState(CornerGrabber::kMouseReleased);

            }
            break;

        case QEvent::GraphicsSceneMouseMove:
            {
                corner->setMouseState(CornerGrabber::kMouseMoving );
            }
            break;

        default:
            // we dont care about the rest of the events
            return false;
            break;
    }


    if ( corner->getMouseState() == CornerGrabber::kMouseMoving )
    {

        qreal x = mevent->pos().x(), y = mevent->pos().y();

        // depending on which corner has been grabbed, we want to move the position
        // of the item as it grows/shrinks accordingly. so we need to eitehr add
        // or subtract the offsets based on which corner this is.

        int XaxisSign = 0;
        int YaxisSign = 0;
        switch( corner->getCorner() )
        {
        case 0:
            {
                XaxisSign = +1;
                YaxisSign = +1;
            }
            break;

        case 1:
            {
                XaxisSign = -1;
                YaxisSign = +1;
            }
            break;

        case 2:
            {
                XaxisSign = -1;
                YaxisSign = -1;
            }
            break;

        case 3:
            {
                XaxisSign = +1;
                YaxisSign = -1;
            }
            break;

        }

        // if the mouse is being dragged, calculate a new size and also re-position
        // the box to give the appearance of dragging the corner out/in to resize the box

        int xMoved = corner->mouseDownX - x;
        int yMoved = corner->mouseDownY - y;

        int newWidth = _width + ( XaxisSign * xMoved);
        if ( newWidth < 40 ) newWidth  = 40;

        int newHeight = _height + (YaxisSign * yMoved) ;
        if ( newHeight < 40 ) newHeight = 40;

        int deltaWidth  =   newWidth - _width ;
        int deltaHeight =   newHeight - _height ;

        adjustSize(  deltaWidth ,   deltaHeight);

        deltaWidth *= (-1);
        deltaHeight *= (-1);

        if ( corner->getCorner() == 0 )
        {
            int newXpos = this->pos().x() + deltaWidth;
            int newYpos = this->pos().y() + deltaHeight;
            this->setPos(newXpos, newYpos);
        }
        else   if ( corner->getCorner() == 1 )
        {
            int newYpos = this->pos().y() + deltaHeight;
            this->setPos(this->pos().x(), newYpos);
        }
        else   if ( corner->getCorner() == 3 )
        {
            int newXpos = this->pos().x() + deltaWidth;
            this->setPos(newXpos,this->pos().y());
        }

        setCornerPositions();

        this->update();
    }

    return true;// true => do not send event to watched - we are finished with this event
}



QRectF GraphicComponent::boundingRect() const
{
    /*qreal radius = _outterborderPen.width()/2; //Create a gap of the pen half
    qreal factor = 2;
    return QRect(-radius,-radius, _width+(factor*radius), _height+(factor*radius));*/
    return QRect(0,0, _width, _height);

}

void GraphicComponent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    /*if (option->state & QStyle::State_Selected)*/

   _outterborderPen.setStyle(Qt::SolidLine);
   painter->setPen(_outterborderPen);

   QPointF topLeft (_drawingOrigenX,_drawingOrigenX);
   QPointF bottomRight ( _drawingWidth , _drawingHeight);

   QRectF rect (topLeft, bottomRight);

   painter->drawPixmap(rect.toRect(),this->pixM);


   if(isSelected())
       {
           QPen selectedPen;
           selectedPen.setColor(Qt::red);
           selectedPen.setWidth(1);
           selectedPen.setStyle(Qt::DashLine);
           painter->setPen(selectedPen);
           painter->drawRect(rect);
       }

}

////////////////////The 3 methods below are not necessary, the moving is handle by setting flags//////////////////////
/*void GraphicComponent::mouseMoveEvent ( QGraphicsSceneMouseEvent * event ){

    QGraphicsItem::mouseMoveEvent(event);

}


void GraphicComponent::mousePressEvent (QGraphicsSceneMouseEvent * event ){

    QGraphicsItem::mousePressEvent(event);


}


void GraphicComponent::mouseReleaseEvent (QGraphicsSceneMouseEvent * event ){

    QGraphicsItem::mouseReleaseEvent(event);

}*/
////////////////////The 3 methods above are not necessary, the moving is handle by setting flags//////////////////////


// remove the corner grabbers

void GraphicComponent::hoverLeaveEvent ( QGraphicsSceneHoverEvent * )
{
    _outterborderColor = Qt::black;

    _corners[0]->setParentItem(NULL);
    _corners[1]->setParentItem(NULL);
    _corners[2]->setParentItem(NULL);
    _corners[3]->setParentItem(NULL);

    delete _corners[0];
    delete _corners[1];
    delete _corners[2];
    delete _corners[3];
}

// create the corner grabbers

void GraphicComponent::hoverEnterEvent ( QGraphicsSceneHoverEvent * )
{
    _outterborderColor = Qt::red;

    _corners[0] = new CornerGrabber(this,0);
    _corners[1] = new CornerGrabber(this,1);
    _corners[2] = new CornerGrabber(this,2);
    _corners[3] = new CornerGrabber(this,3);


    _corners[0]->installSceneEventFilter(this);
    _corners[1]->installSceneEventFilter(this);
    _corners[2]->installSceneEventFilter(this);
    _corners[3]->installSceneEventFilter(this);

    setCornerPositions();

}

void GraphicComponent::setCornerPositions()
{
    /*_corners[0]->setPos(_drawingOrigenX, _drawingOrigenY);
    _corners[1]->setPos(_drawingWidth,  _drawingOrigenY);
    _corners[2]->setPos(_drawingWidth , _drawingHeight);
    _corners[3]->setPos(_drawingOrigenX, _drawingHeight);*/

    _corners[0]->setPos(_drawingOrigenX, _drawingOrigenY);
    _corners[1]->setPos((_drawingWidth-6),  _drawingOrigenY);
    _corners[2]->setPos((_drawingWidth-6) , (_drawingHeight-6));
    _corners[3]->setPos(_drawingOrigenX, (_drawingHeight-6));
}

void GraphicComponent::mouseMoveEvent(QGraphicsSceneDragDropEvent *event)
{
  event->setAccepted(true);
}

void GraphicComponent::mousePressEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setAccepted(true);
}

