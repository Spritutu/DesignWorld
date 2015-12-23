/* Point.h geometry

Date        Author      Remark
20-Nov-2013 srinivas    Intail Version
$HISTORY$*/

#pragma once
#include "Geometry.h"
#include "Vector.h"

struct str_POINT {
    double x;
    double y;
    double z;
    double h;

    str_POINT()
    {
        x = 0;
        y = 0;
        z = 0;
        h = 1;
    }
};

typedef str_POINT SPoint;


class Point :
    public Geometry
{
public:
    //Class Constructors
    Point(void);
    Point(const Point &Point);
    Point(SPoint point);
    Point(int iDim, double dCord[]);
    Point(double x, double y, double z=0, double h = 1);
    ~Point(void);

    double X();
    double Y();
    double Z();

    void ModifyPoint(const Point &point);
    void ModifyPoint(double x, double y, double z=0, double h=1);
    void ModifyPoint(int iDim, double dCoord[]);

    //Operator Overloading
    Point &operator =(const Point &point);
    Point operator +(Point &point);
    Point operator +(Vector &vec);
    
private:
    int m_iDimension;
    SPoint m_point;
};

