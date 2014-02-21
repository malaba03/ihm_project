#ifndef COMPONENTLABEL_H
#define COMPONENTLABEL_H

#include <QLabel>
#include <QString>

class ComponentLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ComponentLabel(QWidget *parent, const char *ressource, int inType);
    void setType(int t);
    int getType();

private:
    int type;

signals:
    
public slots:
    
};

#endif // COMPONENTLABEL_H
