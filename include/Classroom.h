#ifndef CLASSROOM_H
#define CLASSROOM_H

#include "Component.h"
//#include "Corridor.h"

class Classroom : public Component
{
    public:
        Classroom();
        Classroom(std::string nm);

        //void setCorridor(Corridor cor);
        //Corridor getCorridor();
    protected:
    private:
        //Corridor corridor;
};

#endif // CLASSROOM_H
