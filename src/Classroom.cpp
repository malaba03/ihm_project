#include "Classroom.h"

Classroom::Classroom() : Component("new-classroom")
{
    //this.corridor = parent();
}

Classroom::Classroom(std::string nm) : Component(nm)
{
    //this.corridor = parent();
}
void Component::setState(int s)
{state=4;}
void Classroom::setCorridor(Component* cor)
{
    this->corridor = cor;
    //std::cout << "*** Addind corridor" << (this->corridor)->getName()<< std::endl;
}
Component Classroom::getCorridor()
{
    return *(this->corridor);
}

Position Classroom::getNearPosition(Component corridor, Position userPos)
{
    std::cout << " #### IN Classroom ### "<< std::endl;
    std::vector<Door>::iterator iter;
    Position *nearPos = NULL;
    double minDist = 0;
    for (iter=this->doors.begin(); iter!=this->doors.end(); ++iter)
    {
        //if((*iter).getPosition().getPosX())
        double dist = this->calculateDistance(corridor, userPos, (*iter).getPosition());
        if(minDist==0 || dist<minDist){
            *nearPos = (*iter).getPosition();
        }
    }
    if(nearPos==NULL){
        double x, y;
        if(corridor.getPosition().getPosX() > corridor.getPosition().getPosY()){
            x = position.getPosX() + size.getWidth()/2;
            y = position.getPosY();
        }
        else{
            x = position.getPosX();
            y = position.getPosY() + size.getWidth()/2;
        }
        return Position(x, y);
    }
    return *nearPos;
}
