#include "Size.h"

Size::Size()
{}
Size::Size(double w, double h) : width(w), height(h)
{}

void Size::setWidth(double w){this->width=w;}
void Size::setHeight(double h){this->height=h;}

double Size::getWidth(){return this->width;}
double Size::getHeight(){return this->height;}
