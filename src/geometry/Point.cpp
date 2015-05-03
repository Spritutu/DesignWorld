/* Point.cpp geometry

Date        Author      Remark
20-Nov-2013 srinivas    Intail Version
$HISTORY$*/

#include "Point.h"


//Class Constructors

Point::Point(void):
    Geometry(DW_POINT),
    m_iDimension(4),
    x(0),
    y(0),
    z(0),
    h(1)
{
}

Point::Point(const Point &point):
    Geometry(DW_POINT),
    m_iDimension(point.m_iDimension),
    x(point.x),
    y(point.y),
    z(point.z),
    h(point.h)
{
}

Point::Point(int iDim, double dCoord[]):
    Geometry(DW_POINT),
    m_iDimension(iDim),
    x(dCoord[0]),
    y(dCoord[1]),
    z(0),
    h(1)
{
    if( iDim > 2)
    {
        z = dCoord[2];
        if( iDim == 4 )
        {
            h = dCoord[3];
        }
    }
}

Point::Point(double x, double y, double z, double h):
    Geometry(DW_POINT),
    m_iDimension(4),
    x(x),
    y(y),
    z(z),
    h(h)
{

}


void Point::ModifyPoint(const Point &point)
{
    *this = point;
}

void Point::ModifyPoint(double x, double y, double z, double h)
{
    m_iDimension = 4;

    x = x;
    y = y;
    z = z;
    h = h;
}

void Point::ModifyPoint(int iDim, double dCoord[])
{
    m_iDimension = iDim;

    x = dCoord[0];
    y = dCoord[1];
    if( iDim > 2)
    {
        z = dCoord[2];
        if( iDim == 4 )
        {
            h = dCoord[3];
        }
    }
}

//Operator Overloading

Point &Point::operator =(const Point &point)
{
    m_iDimension = point.m_iDimension;
    x = point.x;
    y = point.y;
    z = point.z;
    h = point.h;

    return *this;
}

Point Point::operator +(Point &point)
{
    Point ptTemp;

    ptTemp.x = x + point.x;
    ptTemp.y = y + point.y;
    ptTemp.z = z + point.z;
    ptTemp.h = h + point.h;

    return ptTemp;
}

Point Point::operator +(Vector &vec)
{
    Point ptTemp;

    ptTemp.x = x + vec.x;
    ptTemp.y = y + vec.y;
    ptTemp.z = z + vec.z;
    
    return ptTemp;
}


Point::~Point(void)
{
}
