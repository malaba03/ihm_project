#ifndef COMPONENT_H
#define COMPONENT_H
#include <iostream>
#include <list>
#include <vector>
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
        virtual void setState(int s);
        void setName(std::string nm);

        void addDoor(Door door);
        void removeDoor(Door door);

        Position getPosition();
        Size getSize();
        int getState();
        std::string getName();

        std::vector<Door> getDoors();

        double calculateDistance(Component corridor,Position userPos, Position porte);
        /*virtual Door* getNearDoor(Component corridor, Position userPos)
        {std::cout << " #### IN Component ### "<< std::endl; return NULL;}*/
    protected:
        std::string name;
        Position position;
        Size size;
        int state;
        std::vector<Door> doors;
    private:
};

#endif // COMPONENT_H
