#ifndef RESTROOM_H
#define RESTROOM_H

#include "Component.h"


class Restroom : public Component
{
    public:
        Restroom();
        Restroom(std::string nm);
        void setState(int s)
        {state=s;}
    protected:
    private:
};

#endif // RESTROOM_H
