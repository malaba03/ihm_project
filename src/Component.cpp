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

void Component::setState(int s)
{state=s;}
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

std::list<Door> Component::getDoors()
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
    std::list<Door>::iterator iter;
    for (iter=this->doors.begin(); iter!=this->doors.end(); ++iter)
    {
        if(*iter==door)
        {
            this->doors.remove(door);
        }
    }
}
