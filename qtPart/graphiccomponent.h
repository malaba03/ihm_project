#ifndef GRAPHICCOMPONENT_H
#define GRAPHICCOMPONENT_H

#include "topgraphiccomponent.h"
#include "cornergrabber.h"
#include "popup.h"

#include <QGraphicsItem>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QColor>
#include <QString>
#include <QPainter>
#include <QPen>
#include <QPointF>
#include <QStyleOptionGraphicsItem>
#include <QPixmap>


using namespace std;

class GraphicComponent : public TopGraphicComponent
{
    Q_OBJECT
public:
    GraphicComponent(QPixmap pM, int type);
    ~GraphicComponent();

public slots:
    void setClassroomName(QString newClassroomName);

protected:
    virtual void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event );


private:
    PopUp *changeClassroomNameDialog;
    QGraphicsTextItem _text;

signals:
    


    
};

#endif // GRAPHICCOMPONENT_H
