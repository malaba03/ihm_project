#ifndef DOOR_H
#define DOOR_H

#include <iostream>
#include "Position.h"
#include "Size.h"

class Door
{
    public:
        Door();
        Door(std::string nm);

        bool operator==(const Door& aDoor) const;

        void setPosition(Position p);
        void setSize(Size s);
        void setName(std::string nm);

        int getState();
        Position getPosition();
        Size getSize();
        std::string getName();
    protected:
        std::string name;
        Position position;
        Size size;
        int state;
    private:
};

#endif // DOOR_H
