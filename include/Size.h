#ifndef SIZE_H
#define SIZE_H


class Size
{
    public:
        Size();
        Size(double w, double h);

        void setWidth(double w);
        void setHeight(double h);

        double getWidth();
        double getHeight();
    protected:
    private:
        double width;
        double height;
};

#endif // SIZE_H
