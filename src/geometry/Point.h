/* Point.h geometry

Date        Author      Remark
20-Nov-2013 srinivas    Intail Version
$HISTORY$*/

#pragma once
#include "Geometry.h"
#include "Vector.h"

struct str_POINT {

    double *m_Coord;

    inline double (&x()){ return m_Coord[0]; }
    inline double (&y()){ return m_Coord[1]; }
    inline double (&z()){ return m_Coord[2]; }
    inline double (&h()){ return m_Coord[3]; }


    inline double &x(double x){ m_Coord[0] = x; }
    inline double &y(double y){ m_Coord[1] = y; }
    inline double &z(double z){ m_Coord[2] = z; }
    inline double &h(double h){ m_Coord[3] = h; }

    str_POINT()
    {
        m_Coord = new double[4];
        for (int i = 0; i < THREED; i++)
        {
            m_Coord[i] = 0;
        }
        m_Coord[FOURD] = 1;
    }

    str_POINT(double X, double Y)
    {
        m_Coord = new double[4];
        m_Coord[0] = X;
        m_Coord[1] = Y;
        m_Coord[2] = 0;
        m_Coord[3] = 1;
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

