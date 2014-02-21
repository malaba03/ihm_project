#include "editingview.h"
#include <QGraphicsItem>
#include <QImage>

EditingView::EditingView(QGraphicsScene* scene) :
    QGraphicsView(scene)
{

   this->setAcceptDrops(true);
   this->setAlignment (Qt::AlignLeft | Qt::AlignTop);
   this->setRenderHint(QPainter::Antialiasing);

}

