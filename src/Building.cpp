#include <list>
#include <iostream>
#include <sstream>
#include <cmath>
#include <string>
#include "Building.h"
#include "Corridor.h"
//#include "functions.h"

Building::Building() : Component("new-building")
{}

Building::Building(std::string nm) : Component(nm)
{}

void Building::addLevel(Level level)
{
    this->levels.push_back(level);
}

std::list<Level> Building::getLevels()
{
    return this->levels;
}

void Building::removeLevel(Level level)
{
    std::list<Level>::iterator iter;
    for (iter=this->levels.begin(); iter!=this->levels.end(); ++iter)
    {
        if(*iter==level)
        {
            this->levels.remove(*iter);
        }
    }
}


void Building::setFloor(Level level)
{
    this->floor = level;
}
Level Building::getFloor()
{
    return this->floor;
}

std::vector<Component> Building::findClaasroom(std::string name)
{
    //
    std::vector<Component> results;
    //std::cout << "NB lev:" <<this->levels.size()<< std::endl;
    std::list<Level>::iterator iter_lvl;
    for (iter_lvl=this->levels.begin(); iter_lvl!=this->levels.end(); ++iter_lvl)
    {
        std::list<Corridor> corrs = (*iter_lvl).getCorridors();
        //std::cout << "NB cor:"<< corrs.size() << std::endl;

        std::list<Corridor>::iterator iter_cor;
        for (iter_cor=corrs.begin(); iter_cor!=corrs.end(); ++iter_cor)
        {
            //std::cout << "Corr:" <<(*iter_cor).getName()<< std::endl;

            std::list<Classroom> clsRooms = (*iter_cor).getClassrooms();
            //std::cout << "NB clsrooms:"<< clsRooms.size() << std::endl;

            std::list<Classroom>::iterator iter_cls;
            for (iter_cls=clsRooms.begin(); iter_cls!=clsRooms.end(); ++iter_cls)
            {
                std::cout << "Cls:" <<(*iter_cls).getName()<< std::endl;
                if((*iter_cls).getName()==name){
                    // Calcul chemin
                    //double dist = this->calculateDistanceInCorridor((*iter_cor), Position(570,161), Position(157,165));
                    std::cout << "######OK --- dist:" << (*iter_cls).getName() << std::endl;
                    // chemin =
                    // gauche ou droite
                    // monter ou descendre
                    results.push_back(*iter_cls);
                    results.push_back(*iter_cor);
                    results.push_back(*iter_lvl);
                }
            }
        }
    }
    return results;
}

double Building::calculateDistanceInCorridor(Corridor corridor, Position userPos, Position porte)
{
    double distance;
    if(corridor.getSize().getWidth()>corridor.getSize().getHeight()){
        distance = porte.getPosX()-userPos.getPosX();
    }
    else{
        distance = porte.getPosY()-userPos.getPosY();
    }

    return fabs(distance);
}

std::vector<Component> Building::getLevelAndCorrdidorByPosition(std::string levelName, Position position)
{
    std::vector<Component> results;
    std::list<Level>::iterator iter_lvl;
    for (iter_lvl=this->levels.begin(); iter_lvl!=this->levels.end(); ++iter_lvl)
    {
        if((*iter_lvl).getName()==levelName){
            std::list<Corridor> corrs = (*iter_lvl).getCorridors();
            //std::cout << "NB cor:"<< corrs.size() << std::endl;

            std::list<Corridor>::iterator iter_cor;
            for (iter_cor=corrs.begin(); iter_cor!=corrs.end(); ++iter_cor)
            {
                //std::cout << "Corr:" <<(*iter_cor).getName()<< std::endl;

                std::list<Classroom> clsRooms = (*iter_cor).getClassrooms();
                //std::cout << "NB clsrooms:"<< clsRooms.size() << std::endl;

                //Position p1 = (*iter_cor).getPosition();
                double xCorner1 = (*iter_cor).getPosition().getPosX();
                double yCorner1 = (*iter_cor).getPosition().getPosY();

                //std::cout << "Xp1:"<< xCorner1<< "Yp1:"<< yCorner1 << std::endl;

                double xCorner4 = xCorner1+(*iter_cor).getSize().getWidth();
                double yCorner4 = yCorner1+(*iter_cor).getSize().getHeight();
                //std::cout << "Xp4:"<< xCorner4<< "Yp4:"<< yCorner4 << std::endl;

                if((position.getPosX()>xCorner1 && position.getPosY()>yCorner1) && (position.getPosX()<xCorner4 && position.getPosY()<yCorner4)){
                    //std::cout << "++++Corr found:"<< (*iter_cor).getName()<< std::endl;
                    results.push_back(*iter_cor);
                    results.push_back(*iter_lvl);
                    //return (*iter_cor);
                }
            }
        }
    }
    return results;
}


//void findPath(Position usrPos, Level level, Classroom classroom)
void Building::findPath(std::string clsName, std::string lvlUsr, Position userPos)
{
    std::vector<Component> infosCls = this->findClaasroom(clsName);
    if(infosCls.size()==3){
        std::cout << "---- OK a classroom found ----" << std::endl;
        std::vector<Component> rsUsr = this->getLevelAndCorrdidorByPosition(lvlUsr, userPos);
        if(rsUsr.size()==2){
            std::cout << "---- OK a lvel&corr user found ----" << std::endl;
            Classroom* clsFound = (Classroom*)&infosCls[0];
            Component corrFound = infosCls[1];
            Component lvlFound = infosCls[2];

            Component userCorr = rsUsr[0];
            Component usrLvl = rsUsr[1];

            if(usrLvl==lvlFound){
                std::cout << "---- OK same level ----" << std::endl;
                if(userCorr==corrFound){
                    std::cout << "---- OK same corridor ----" << std::endl;
                    Position nearPos = clsFound->getNearPosition(userCorr, userPos);
                    std::cout << "---- NearPos ---- X=" << nearPos.getPosX() << " Y=" << nearPos.getPosY() << std::endl;

                    double dist = this->calculateDistance(userCorr, userPos, nearPos);
                    std::cout << "-- Walk -- " << dist << " m." << std::endl;
                }
                else{
                    //retrieve by junctions between corridors

                }
            }
            else{

            }
        }
        else{
            std::cout << "---- ERROR any lvel&corr user found ----" << std::endl;
        }
    }
    else{
        std::cout << "---- Any classroom found ----" << std::endl;
    }
}
/*
std::list getAllPaths(Corridor corridor, Corridor userCorr){
    std::vector<std::vector<Corridor>> allPaths;
    std::list<Corridor>::iterator iter_cor;
    debut = corridor.junctions.begin();
    std::vector<Corridor> aPath;
    while(debut!=corrs.end())
    {

    }
}*/

const char* doubleToWchar(double value)
{
    std::ostringstream ss;
    ss << value;
    //s = ss.str();
    return ss.str().c_str();
}

XtreMLNODE* putDoors(XtreMLNODE *node, Component component){
    if(component.getDoors().size()>0){
        XtreMLNODE *_tmpDoor;
        _tmpDoor = node->NodeAdd("doors");
        std::vector<Door> doors = component.getDoors();
        std::vector<Door>::iterator iter_dor;
        for (iter_dor=doors.begin(); iter_dor!=doors.end(); ++iter_dor)
        {
            _tmpDoor = _tmpDoor->NodeAdd("door");                                  // current level
            // Add attributes to corridor
            //_tmpDoor->AttrAdd("name",(*iter_dor).getName().c_str());
            _tmpDoor->AttrAdd("posX", doubleToWchar((*iter_dor).getPosition().getPosX()));
            _tmpDoor->AttrAdd("posY", doubleToWchar((*iter_dor).getPosition().getPosY()));
            _tmpDoor->AttrAdd("width", doubleToWchar((*iter_dor).getSize().getWidth()));
            _tmpDoor->AttrAdd("height", doubleToWchar((*iter_dor).getSize().getHeight()));
            _tmpDoor->AttrAdd("state", doubleToWchar((*iter_dor).getState()));

            //_tmpDoor = document.FindNode("doors");
            _tmpDoor = _tmpDoor.GetContainer();
        }
    }
    return node;
}
void Building::exporteToXml(){
    UTF16String  string;
    XtreMLDocument document;
    XtreMLNODE *root, *_tmpLvl, *_tmpCorr, *_tmpClsr;//, _tmpRstr, _tmpDoor, _tmpElv, _tmpStair;    //avec 2 noeuds temporaires on peut créer n'importe quel type de document XML
    document.ProcessingAdd("xml version=\"1.0\" encoding=\"UTF-8\"");// on ajoute le prologue.

    root = document.NodeAdd("building");
    root = root->NodeAdd("levels");
    // Add levels start
    std::list<Level> levels = this->getLevels();
    std::list<Level>::iterator iter_lvl;
    for (iter_lvl=levels.begin(); iter_lvl!=levels.end(); ++iter_lvl)
    {
        _tmpLvl = root->NodeAdd("level");                                  // current level
        // Add attributes to level
        _tmpLvl->AttrAdd("name",(*iter_lvl).getName().c_str());
        _tmpLvl->AttrAdd("posX", doubleToWchar((*iter_lvl).getPosition().getPosX()));
        _tmpLvl->AttrAdd("posY", doubleToWchar((*iter_lvl).getPosition().getPosY()));
        _tmpLvl->AttrAdd("width", doubleToWchar((*iter_lvl).getSize().getWidth()));
        _tmpLvl->AttrAdd("height", doubleToWchar((*iter_lvl).getSize().getHeight()));
        _tmpLvl->AttrAdd("state", doubleToWchar((*iter_lvl).getState()));

        _tmpLvl = putDoors(_tmpLvl);

        // Add Corridor start
        _tmpCorr = _tmpLvl->NodeAdd("corridors");
        std::list<Corridor> corridors = (*iter_lvl).getCorridors();
        std::list<Corridor>::iterator iter_corr;
        for (iter_corr=corridors.begin(); iter_corr!=corridors.end(); ++iter_corr)
        {
            _tmpCorr = _tmpCorr->NodeAdd("corridor");                                  // current level
            // Add attributes to corridor
            _tmpCorr->AttrAdd("name",(*iter_corr).getName().c_str());
            _tmpCorr->AttrAdd("posX", doubleToWchar((*iter_corr).getPosition().getPosX()));
            _tmpCorr->AttrAdd("posY", doubleToWchar((*iter_corr).getPosition().getPosY()));
            _tmpCorr->AttrAdd("width", doubleToWchar((*iter_corr).getSize().getWidth()));
            _tmpCorr->AttrAdd("height", doubleToWchar((*iter_corr).getSize().getHeight()));
            _tmpCorr->AttrAdd("state", doubleToWchar((*iter_corr).getState()));

            // Add Classroom start
            _tmpClsr = _tmpCorr->NodeAdd("classrooms");
            std::list<Classroom> classrooms =  (*iter_corr).getClassrooms();
            std::list<Classroom>::iterator iter_clsr;
            for (iter_clsr=classrooms.begin(); iter_clsr!=classrooms.end(); ++iter_clsr)
            {
                _tmpClsr = _tmpClsr->NodeAdd("classroom");                                  // current level
                // Add attributes to corridor
                _tmpClsr->AttrAdd("name",(*iter_clsr).getName().c_str());
                _tmpClsr->AttrAdd("posX", doubleToWchar((*iter_clsr).getPosition().getPosX()));
                _tmpClsr->AttrAdd("posY", doubleToWchar((*iter_clsr).getPosition().getPosY()));
                _tmpClsr->AttrAdd("width", doubleToWchar((*iter_clsr).getSize().getWidth()));
                _tmpClsr->AttrAdd("height", doubleToWchar((*iter_clsr).getSize().getHeight()));
                _tmpClsr->AttrAdd("state", doubleToWchar((*iter_clsr).getState()));
                // Add doors start
                // Add do0rs end
                _tmpClsr = document.FindNode("classrooms");
            }// Add Classroom end

            //Add Restrooms start
            //Add Restrooms end

            _tmpCorr = document.FindNode("corridors");
        }// Add Corridor end

        _tmpLvl = document.FindNode("levels");
    }// Add levels end

    char lpBuffer[256];
    GetCurrentDirectoryA(256, lpBuffer); //on récuperer le répertoire  courant
    string = lpBuffer;
    string += "\\";
    string += "my_building-2.xml";  //construction du nom complet du fichier de sortie
    document.SaveToFile(string.w_str(), EncUTF8, true);// on enregistre le document au format UTF-8, avec le BOM
}
