#include "functions.h"

char* doubleToWchar(double value)
{
    stringstream sstr;
    sstr << value;
    return sstr.str().c_str();
}
/*
double calculateDistance(Component corridor, Position position1, Position position2)
{
    if(corridor.getSize().getWidth()>corridor.getSize().getHeight()){
        distance = position2.getPosX()-position1.getPosX();
    }
    else{
        distance = position2.getPosY()-position1.getPosY();
    }
    return fabs(distance);
}

void exorteXmle(Building building){
    UTF16String  string;
    XtreMLDocument document;
    XtreMLNODE *root, *_tmpLvl, *_tmpCorr, _tmpClsr, _tmpRstr, _tmpDoor, _tmpElv, _tmpStair;    //avec 2 noeuds temporaires on peut créer n'importe quel type de document XML
    document.ProcessingAdd("xml version=\"1.0\" encoding=\"UTF-8\"");// on ajoute le prologue.

    root = document.NodeAdd("building");
    root = root->NodeAdd("levels");
    // Add levels start
    std::list<Level> levels getLevels();
    std::list<Level>::iterator iter_lvl;
    for (iter_lvl=levels.begin(); iter_lvl!=levels.end(); ++iter_lvl)
    {
        _tmpLvl = node->NodeAdd("level");                                  // current level
        // Add attributes to level
        _tmpLvl->AttrAdd("name",(*iter_lvl)->getName());
        _tmpLvl->AttrAdd("posX", (*iter_lvl)->getPosition()->getPosX());
        _tmpLvl->AttrAdd("posY", (*iter_lvl)->getPosition()->getPosY());
        _tmpLvl->AttrAdd("width", (*iter_lvl)->getSize()->getWidth());
        _tmpLvl->AttrAdd("height", (*iter_lvl)->getSize()->getHeight());
        _tmpLvl->AttrAdd("state", (*iter_lvl)->getSize()->getState());

        // Add Corridor start
        _tmpCorr = _tmpLvl->NodeAdd("corridors");
        std::list<Corridor> corridors = (*iter_lvl)->getLevels();
        std::list<Corridor>::iterator iter_corr;
        for (iter_corr=corridors.begin(); iter_corr!=corridors.end(); ++iter_corr)
        {
            _tmpCorr = node->NodeAdd("corridor");                                  // current level
            // Add attributes to corridor
            _tmpCorr->AttrAdd("name",(*iter_corr)->getName());
            _tmpCorr->AttrAdd("posX", (*iter_corr)->getPosition()->getPosX());
            _tmpCorr->AttrAdd("posY", (*iter_corr)->getPosition()->getPosY());
            _tmpCorr->AttrAdd("width", (*iter_corr)->getSize()->getWidth());
            _tmpCorr->AttrAdd("height", (*iter_corr)->getSize()->getHeight());
            _tmpCorr->AttrAdd("state", (*iter_corr)->getSize()->getState());

            // Add Classroom start
            _tmpClsr = _tmpCorr->NodeAdd("classrooms");
            std::list<Classroom> classrooms =  (*iter_corr)->getClassrooms();
            std::list<Classroom>::iterator iter_clsr;
            for (iter_clsr=classrooms.begin(); iter_clsr!=classrooms.end(); ++iter_clsr)
            {
                _tmpClsr = node->NodeAdd("classroom");                                  // current level
                // Add attributes to corridor
                _tmpClsr->AttrAdd("name",(*iter_clsr)->getName());
                _tmpClsr->AttrAdd("posX", (*iter_clsr)->getPosition()->getPosX());
                _tmpClsr->AttrAdd("posY", (*iter_clsr)->getPosition()->getPosY());
                _tmpClsr->AttrAdd("width", (*iter_clsr)->getSize()->getWidth());
                _tmpClsr->AttrAdd("height", (*iter_clsr)->getSize()->getHeight());
                _tmpClsr->AttrAdd("state", (*iter_clsr)->getSize()->getState());
                // Add doors start
                // Add do0rs end
            }// Add Classroom end

            //Add Restrooms start
            //Add Restrooms end
        }// Add Corridor end
    }// Add levels end

    char lpBuffer[256];
    GetCurrentDirectoryA(256, lpBuffer); //on récuperer le répertoire  courant
    string = lpBuffer;
    string += "\\";
    string += "my_building.xml";  //construction du nom complet du fichier de sortie
    document.SaveToFile(string.w_str(), EncUTF8, true);// on enregistre le document au format UTF-8, avec le BOM
}
*/
