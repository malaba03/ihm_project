#ifndef BUILDING_H
#define BUILDING_H

#include "Component.h"
#include "Level.h"

class Building : public Component
{
    public:
        Building();
        Building(std::string nm);

        void addLevel(Level level);
        void removeLevel(Level level);

        void setFloor(Level level);
        Level getFloor();

        std::list<Level> getLevels();

        void findPath(std::string name);
    protected:
    private:
        Level floor;
        std::list<Level> levels;
};

#endif // BUILDING_H
