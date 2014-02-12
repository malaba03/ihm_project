#ifndef CORRIDOR_H
#define CORRIDOR_H

#include "Component.h"
//#include "Level.h"
#include "Classroom.h"
#include "Restroom.h"
#include "Stair.h"
#include "Elevator.h"


class Corridor : public Component
{
    public:
        Corridor();
        Corridor(std::string nm);

        void addClassroom(Classroom classroom);
        void addRestroom(Restroom restroom);

        void addStair(Stair stair);
        void addElevator(Elevator elevator);

        std::list<Classroom> getClassrooms();
        std::list<Restroom> getRestrooms();

        std::list<Stair> getStairs();
        std::list<Elevator> getElevators();

        void removeClassroom(Classroom classroom);
        void removeRestroom(Restroom restroom);
        void removeStair(Stair stair);
        void removeElevator(Elevator elevator);

        //void findPath(std::string className);
    protected:
    private:
        std::list<Classroom> classrooms;
        std::list<Restroom> restrooms;

        std::list<Stair> stairs;
        std::list<Elevator> elevators;
};

#endif // CORRIDOR_H
