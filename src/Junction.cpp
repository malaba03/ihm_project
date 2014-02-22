#include "Junction.h"

Junction::Junction(Component cor, Position p) : corridor(cor), point(p)
{}
bool Junction::operator==(const Junction& aJunction) const
{
    return (corridor==aJunction.corridor);
}
void Junction::seCorridor(Component cor)
{
    this->corridor = cor;
}
void Junction::setPosition(Position p)
{
    this->point = p;
}

Component Junction::getCorridor()
{
    return this->corridor;
}
Position Junction::getPosition()
{
    return this->point;
}
