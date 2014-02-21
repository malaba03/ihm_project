#ifndef EDITINGVIEW_H
#define EDITINGVIEW_H

#include <QGraphicsView>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>

class EditingView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit EditingView(QGraphicsScene *scene);
    


signals:
    
public slots:
    
};

#endif // EDITINGVIEW_H
