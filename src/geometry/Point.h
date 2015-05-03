/* Point.h geometry

Date        Author      Remark
20-Nov-2013 srinivas    Intail Version
$HISTORY$*/

#pragma once
#include "Geometry.h"
#include "Vector.h"

class Point :
    public Geometry
{
public:
    //Class Constructors
    Point(void);
    Point(const Point &Point);
    Point(int iDim, double dCord[]);
    Point(double x, double y, double z=0, double h = 1);
    ~Point(void);

    void ModifyPoint(const Point &point);
    void ModifyPoint(double x, double y, double z=0, double h=1);
    void ModifyPoint(int iDim, double dCoord[]);

    //Operator Overloading
    Point &operator =(const Point &point);
    Point operator +(Point &point);
    Point operator +(Vector &vec);
    
public:
    int m_iDimension;
    double x, y, z, h;
};

