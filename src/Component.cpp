#include <cmath>
#include "Component.h"

Component::Component(std::string n) : name(n)
{}

bool Component::operator==(const Component& aComponent) const
{
    return (name==aComponent.name);
}
void Component::setPosition(Position p)
{position=p;}

void Component::setSize(Size s)
{size=s;}

void Component::setName(std::string nm)
{this->name = nm;}

//GETTERS

Position Component::getPosition()
{return position;}

Size Component::getSize()
{return this->size;}

int Component::getState()
{return state;}

std::string Component::getName()
{return this->name;}

std::vector<Door> Component::getDoors()
{
    return this->doors;
}

//OTHERS
void Component::addDoor(Door door)
{
    this->doors.push_back(door);
}

void Component::removeDoor(Door door)
{
    std::vector<Door>::iterator iter;
    for (iter=this->doors.begin(); iter!=this->doors.end(); ++iter)
    {
        if(*iter==door)
        {
            this->doors.erase(iter);
        }
    }
}

double Component::calculateDistance(Component corridor, Position position1, Position position2)
{
    double distance;
    if(corridor.getSize().getWidth()>corridor.getSize().getHeight()){
        distance = position2.getPosX()-position1.getPosX();
    }
    else{
        distance = position2.getPosY()-position1.getPosY();
    }
    return fabs(distance);
}
