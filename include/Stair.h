#ifndef STAIR_H
#define STAIR_H

#include "Component.h"


class Stair : public Component
{
    public:
        Stair();
        Stair(std::string nm);
        void setState(int s)
        {state=s;}
    protected:
    private:
};

#endif // STAIR_H
