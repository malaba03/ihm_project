#ifndef POSITION_H
#define POSITION_H


class Position
{
    public:
        Position();
        Position(double x, double y);

        void setPosX(double x);
        void setPosY(double y);

        double getPosX();
        double getPosY();
    protected:
    private:
        double posX;
        double posY;
};

#endif // POSITION_H
