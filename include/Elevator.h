#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "Component.h"


class Elevator : public Component
{
    public:
        Elevator();
        Elevator(std::string nm);
        void setState(int s)
        {state=s;}
    protected:
    private:
};

#endif // ELEVATOR_H
