/* Point.cpp geometry

Date        Author      Remark
20-Nov-2013 srinivas    Intail Version
$HISTORY$*/

#include "Point.h"


//Class Constructors

Point::Point(void):
    Geometry(GEOM_POINT),
    m_iDimension(4)
{
    m_Coord = new double[m_iDimension];
    for (int i = 0; i < m_iDimension; i++)
    {
        m_Coord[i] = 0;
    }
}

Point::Point(const Point &point):
    Geometry(GEOM_POINT),
    m_iDimension(point.m_iDimension)
{
    m_Coord = new double[m_iDimension];
    for (int i = 0; i < m_iDimension; i++)
    {
        m_Coord[i] = point.m_Coord[i];
    }
}

Point::Point(SPoint point):
    Geometry(GEOM_POINT),
    m_iDimension(4)
{
    m_Coord = new double[m_iDimension];

    m_Coord[0] = point.x;
    m_Coord[1] = point.y;
    m_Coord[2] = point.z;
    m_Coord[3] = point.h;
}
Point::Point(int iDim, double dCoord[]):
    Geometry(GEOM_POINT),
    m_iDimension(iDim)
{
    m_Coord = new double[m_iDimension];
    for (int i = 0; i < m_iDimension; i++)
    {
        m_Coord[i] = dCoord[i];
    }
}

Point::Point(double x, double y, double z, double h):
    Geometry(GEOM_POINT),
    m_iDimension(4)
{
    m_Coord = new double[m_iDimension];

    m_Coord[0] = x;
    m_Coord[1] = y;
    m_Coord[2] = z;
    m_Coord[3] = h;
}


void Point::ModifyPoint(const Point &point)
{
    *this = point;
}

void Point::ModifyPoint(double x, double y, double z, double h)
{
    m_iDimension = 4;
    
    m_Coord = new double[m_iDimension];

    m_Coord[0] = x;
    m_Coord[1] = y;
    m_Coord[2] = z;
    m_Coord[3] = h;
}

void Point::ModifyPoint(int iDim, double dCoord[])
{
    if (m_iDimension != iDim)
    {
        m_iDimension = iDim;

        if (m_Coord)
        {
            delete[] m_Coord;
            m_Coord = nullptr;
        }

        m_Coord = new double[m_iDimension];
    }


    for (int i = 0; i < m_iDimension; i++)
    {
        m_Coord[i] = dCoord[i];
    }
}

//Operator Overloading

Point &Point::operator =(const Point &point)
{
    if (m_iDimension != point.m_iDimension)
    {
        m_iDimension = point.m_iDimension;

        if (m_Coord)
        {
            delete [] m_Coord;
            m_Coord = nullptr;
        }

        m_Coord = new double[m_iDimension];
    }

    
    for (int i = 0; i < m_iDimension; i++)
    {
        m_Coord[i] = point.m_Coord[i];
    }

    return *this;
}

Point Point::operator +(Point &point)
{
    Point ptTemp;

    for (int i = 0; i < m_iDimension; i++)
    {
        ptTemp.m_Coord[i] = m_Coord[i] + point.m_Coord[i];
    }

    return ptTemp;
}

Point Point::operator +(Vector &vec)
{
    Point ptTemp;

    ptTemp.m_Coord[0] = m_Coord[0] + vec.x;
    ptTemp.m_Coord[1] = m_Coord[1] + vec.y;
    ptTemp.m_Coord[2] = m_Coord[2] + vec.z;
    
    return ptTemp;
}


Point::~Point(void)
{
    if (m_Coord)
    {
        delete[] m_Coord;
        m_Coord = nullptr;
    }
}

double Point::X()
{
    return m_Coord[0];
}

double Point::Y()
{
    return m_Coord[1];
}

double Point::Z()
{
    return m_Coord[2];
}