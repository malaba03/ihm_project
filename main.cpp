#include <iostream>
#include "include/Building.h"
using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    //batiment
    Building building("bat14");

    // levels
    Level nivo_0("00");
    Level nivo_1("01");
    Level nivo_2("02");

    //corridors 001
    Corridor c001("C001");
    //c001.setPosition(Position(565, 2));
    //c001.setSize(Size(39, 259));
        // salle
        Classroom class39("039");
        class39.setPosition(Position(609, 172));
        class39.setSize(Size(75, 133));
        c001.addClassroom(class39);


    //corridors 002
    Corridor c002("C002");
    c002.setPosition(Position(565, 2));
    c002.setSize(Size(39, 259));
       // salles
        Restroom s001("S001");
        Restroom s002("S002");
        Restroom s003("S003");
        c002.addRestroom(s001);
        c002.addRestroom(s002);
        c002.addRestroom(s003);

    // corridor 003
    Corridor c003("C003");
    c003.setPosition(Position(120, 145));
    c003.setSize(Size(492, 21));
        Classroom class331("033.1");
            class331.setPosition(Position(121, 166));
            class331.setSize(Size(41, 119));

        Classroom class34("34");
            class34.setPosition(Position(84, 7));
            class34.setSize(Size(160, 134));

        Classroom class35("35");
            class35.setPosition(Position(166, 166));
            class35.setSize(Size(160, 134));

        Classroom class351("0351");
            class351.setPosition(Position(324, 167));
            class351.setSize(Size(78, 134));

        Classroom class36("36");
            class36.setPosition(Position(242, 7));
            class36.setSize(Size(121, 134));

        Classroom class37("37");
            class37.setPosition(Position(405, 167));
            class37.setSize(Size(37, 134));

        Classroom class371("0371");
            class371.setPosition(Position(445, 167));
            class371.setSize(Size(116, 134));

        Classroom class38("38");
            class38.setPosition(Position(364, 7));
            class38.setSize(Size(121, 134));

        Classroom class381("0381");
            class381.setPosition(Position(485, 7));
            class381.setSize(Size(77, 134));

        c003.addClassroom(class331);
         //class331.getCorridor();
        c003.addClassroom(class34);
        c003.addClassroom(class35);
        c003.addClassroom(class351);
        c003.addClassroom(class36);
        c003.addClassroom(class37);
        c003.addClassroom(class371);
        c003.addClassroom(class38);
        c003.addClassroom(class381);



    // corridor C004
    Corridor c004("C004");
    c004.setPosition(Position(7, 144));
    c004.setSize(Size(114, 24));
        // create classrooms
        Classroom class33("33");
            class33.setPosition(Position(6, 144));
            class33.setSize(Size(113, 161));

        c004.addClassroom(class33);
        c004.addClassroom(class34);

    //add corridors
    nivo_0.addCorridor(c001);
    nivo_0.addCorridor(c002);
    nivo_0.addCorridor(c003);
    nivo_0.addCorridor(c004);

    building.addLevel(nivo_0);

    building.findPath(class331.getName(),nivo_0.getName(), Position(556, 156));

    building.exporteToXml();
    //building.getCorrdidorFromPosition(nivo_0.getName(), Position(578, 62));

    //Component* mnCorr = class331.getCorridor();

    //cout << "Class:" << class331.getName() << " => Corridor:" << class331.getCorridor()<< endl;
    return 0;
}
