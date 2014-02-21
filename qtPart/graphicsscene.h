#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsItem>
#include <QPainter>
#include <QRect>
#include "graphiccomponent.h"
#include "graphicclassroomcomponent.h"

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicsScene(QObject *parent = 0);
    GraphicComponent *tempGraphicComponent;
    QList<QGraphicsItem> *allComponentContains;


protected:
    virtual void dragEnterEvent ( QGraphicsSceneDragDropEvent * event );
   virtual void dragLeaveEvent ( QGraphicsSceneDragDropEvent * event );
    virtual void dragMoveEvent ( QGraphicsSceneDragDropEvent * event );
    virtual void dropEvent ( QGraphicsSceneDragDropEvent * event );
    virtual void 	drawBackground ( QPainter * painter, const QRectF & rect );
signals:

public slots:
    void deleteComponents();

};

#endif // GRAPHICSSCENE_H
