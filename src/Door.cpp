#include "Door.h"


Door::Door() : name("new-door"), state(0)
{}
Door::Door(std::string nm) : name(nm), state(0)
{}

bool Door::operator==(const Door& aDoor) const
{
    return (name==aDoor.name);
}

void Door::setPosition(Position p)
{position=p;}

void Door::setSize(Size s)
{size=s;}

void Door::setName(std::string nm)
{this->name = nm;}

//GETTERS

Position Door::getPosition()
{return position;}

Size Door::getSize()
{return this->size;}

int Door::getState()
{return state;}

std::string Door::getName()
{return this->name;}
