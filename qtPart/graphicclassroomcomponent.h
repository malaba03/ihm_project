#ifndef GRAPHICCLASSROOMCOMPONENT_H
#define GRAPHICCLASSROOMCOMPONENT_H

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
#include <graphiccomponent.h>
#include "cornergrabber.h"
#include "popup.h"

using namespace std;

class GraphicClassroomComponent : public GraphicComponent
{
    Q_OBJECT
public:
    GraphicClassroomComponent(QPixmap pM, int type);
    ~GraphicClassroomComponent();

public slots:
    void setClassroomName(QString newClassroomName);

protected:
    virtual void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event );


private:
    PopUp *changeClassroomNameDialog;
    QGraphicsTextItem _text;

signals:
    


    
};

#endif // GRAPHICCLASSROOMCOMPONENT_H
