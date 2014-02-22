#ifndef CLASSROOM_H
#define CLASSROOM_H

#include "Component.h"
//#include "Corridor.h"
//#include "functions.h"

class Classroom : public Component
{
    public:
        Classroom();
        Classroom(std::string nm);

        void setCorridor(Component* cor);
        Component getCorridor();
        //Component* corridor;
        Position getNearPosition(Component corridor, Position userPos);
    protected:
    private:
       Component* corridor;
};

#endif // CLASSROOM_H
