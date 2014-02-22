#ifndef JUNCTION_H
#define JUNCTION_H
#include "Component.h"
#include "Position.h"


class Junction
{
    public:
        Junction(Component cor, Position p);
        bool operator==(const Junction& aJunction) const;
        void seCorridor(Component cor);
        void setPosition(Position p);

        Component getCorridor();
        Position getPosition();
    protected:
    private:
        Component corridor;
        Position point;
};

#endif // JUNCTION_H
