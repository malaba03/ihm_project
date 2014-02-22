#include "Position.h"

Position::Position() : posX(0), posY(0)
{}

Position::Position(double x, double y): posX(x), posY(y)
{}
bool Position::operator==(const Position& aPosition) const
{
    return (posX==aPosition.posX && posY==aPosition.posY);
}
void Position::setPosX(double x)
{
    this->posX=x;
}
void Position::setPosY(double y)
{
    this->posY=y;
}

double Position::getPosX(){
    return this->posX;
}

double Position::getPosY()
{
    return this->posY;
}
