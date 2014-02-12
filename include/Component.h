#ifndef COMPONENT_H
#define COMPONENT_H
#include <iostream>
#include <list>
#include "Door.h"
#include "Position.h"
#include "Size.h"


class Component
{
    public:
        Component(std::string nm);

        bool operator==(const Component& aComponent) const;

        void setPosition(Position p);
        void setSize(Size s);
        void setState(int s);
        void setName(std::string nm);

        void addDoor(Door door);
        void removeDoor(Door door);

        Position getPosition();
        Size getSize();
        int getState();
        std::string getName();

        std::list<Door> getDoors();
    protected:
        std::string name;
        Position position;
        Size size;
        int state;
        std::list<Door> doors;
    private:
};

#endif // COMPONENT_H
