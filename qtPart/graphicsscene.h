#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include "graphiccomponent.h"



#include <QGraphicsScene>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsItem>
#include <QPainter>
#include <QRect>
#include <QString>

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicsScene(QString layerFil);
    GraphicComponent *tempGraphicComponent;
    QList<QGraphicsItem> *allComponentContains;


    QString getLayerFile() const;
    void setLayerFile(const QString &value);

protected:
    virtual void dragEnterEvent ( QGraphicsSceneDragDropEvent * event );
   virtual void dragLeaveEvent ( QGraphicsSceneDragDropEvent * event );
    virtual void dragMoveEvent ( QGraphicsSceneDragDropEvent * event );
    virtual void dropEvent ( QGraphicsSceneDragDropEvent * event );
    virtual void 	drawBackground ( QPainter * painter, const QRectF & rect );
signals:

private:
    QString layerFile;


public slots:
    void deleteComponents();

};

#endif // GRAPHICSSCENE_H
