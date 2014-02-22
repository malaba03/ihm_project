#ifndef BUILDING_H
#define BUILDING_H
#include <vector>
#include "../libxml/stdafx.h"
#include "../libxml/XtreMLParser.h"
#include "Component.h"
#include "Level.h"
#include "Corridor.h"


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

        std::vector <Component> findClaasroom(std::string name);
        void findPath(std::string clsName, std::string lvlUsr, Position userPos);
        std::vector<Component> getLevelAndCorrdidorByPosition(std::string levelName, Position position);
        double calculateDistanceInCorridor(Corridor corridor, Position userPos, Position porte);
        void exporteToXml();
    protected:
    private:
        Level floor;
        std::list<Level> levels;
};

#endif // BUILDING_H
