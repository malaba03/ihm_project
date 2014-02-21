#include "componentlabel.h"

ComponentLabel::ComponentLabel(QWidget *parent, const char *ressource, int inType):
    QLabel(parent),
    type(inType)
{

    //setPixmap(QPixmap(":/images/classroom.jpg"));
    setPixmap(QPixmap(ressource));
    move(10, 10);
    show();
    setAttribute(Qt::WA_DeleteOnClose);

}

void ComponentLabel::setType(int t){

    this->type=t;

}
int ComponentLabel::getType(){


    return this->type;

}
