/* Point.cpp geometry

Date        Author      Remark
20-Nov-2013 srinivas    Intail Version
$HISTORY$*/

#include "Point.h"


//Class Constructors

Point::Point(void):
    Geometry(DW_POINT),
    m_iDimension(4)
{
    m_point.x = 0;
    m_point.y = 0;
    m_point.z = 0;
    m_point.h = 0;
}

Point::Point(const Point &point):
    Geometry(DW_POINT),
    m_iDimension(point.m_iDimension)
{
    m_point.x = point.m_point.x;
    m_point.y = point.m_point.y;
    m_point.z = point.m_point.z;
    m_point.h = point.m_point.h;
}

Point::Point(SPoint point):
    Geometry(DW_POINT),
    m_iDimension(4)
{
    m_point.x = point.x;
    m_point.y = point.y;
    m_point.z = point.z;
    m_point.h = point.h;
}
Point::Point(int iDim, double dCoord[]):
    Geometry(DW_POINT),
    m_iDimension(iDim)
{
    m_point.x = dCoord[0];
    m_point.y = dCoord[1];
    m_point.z = 0;
    m_point.h = 1;

    if( iDim > 2)
    {
        m_point.z = dCoord[2];
        if( iDim == 4 )
        {
            m_point.h = dCoord[3];
        }
    }
}

Point::Point(double x, double y, double z, double h):
    Geometry(DW_POINT),
    m_iDimension(4)
{
    m_point.x = x;
    m_point.y = y;
    m_point.z = z;
    m_point.h = h;
}


void Point::ModifyPoint(const Point &point)
{
    *this = point;
}

void Point::ModifyPoint(double x, double y, double z, double h)
{
    m_iDimension = 4;

    m_point.x = x;
    m_point.y = y;
    m_point.z = z;
    m_point.h = h;
}

void Point::ModifyPoint(int iDim, double dCoord[])
{
    m_iDimension = iDim;

    m_point.x = dCoord[0];
    m_point.y = dCoord[1];
    if( iDim > 2)
    {
        m_point.z = dCoord[2];
        if( iDim == 4 )
        {
            m_point.h = dCoord[3];
        }
    }
}

//Operator Overloading

Point &Point::operator =(const Point &point)
{
    m_iDimension = point.m_iDimension;
    m_point.x = point.m_point.x;
    m_point.y = point.m_point.y;
    m_point.z = point.m_point.z;
    m_point.h = point.m_point.h;

    return *this;
}

Point Point::operator +(Point &point)
{
    Point ptTemp;

    ptTemp.m_point.x = m_point.x + point.m_point.x;
    ptTemp.m_point.y = m_point.y + point.m_point.y;
    ptTemp.m_point.z = m_point.z + point.m_point.z;
    ptTemp.m_point.h = m_point.h + point.m_point.h;

    return ptTemp;
}

Point Point::operator +(Vector &vec)
{
    Point ptTemp;

    ptTemp.m_point.x = m_point.x + vec.x;
    ptTemp.m_point.y = m_point.y + vec.y;
    ptTemp.m_point.z = m_point.z + vec.z;
    
    return ptTemp;
}


Point::~Point(void)
{
}

double Point::X()
{
    return m_point.x;
}

double Point::Y()
{
    return m_point.y;
}

double Point::Z()
{
    return m_point.z;
}