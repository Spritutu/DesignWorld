/* Line.cpp geometry

Date        Author      Remark
17-Nov-2013 srinivas    Intail Version
$HISTORY$*/

#include "Line.h"

//Class Constructors

Line::Line(void):
    Geometry(GEOM_LINE),
    m_ptStart(),
    m_ptEnd()
{
}

Line::Line(Point ptStart, Point ptEnd):
    Geometry(GEOM_LINE),
    m_ptStart(ptStart),
    m_ptEnd(ptEnd)
{
}

Line::Line(Point ptOrigin, Vector vDirection, double dParam):
    Geometry(GEOM_LINE),
    m_ptStart(ptOrigin),
    m_ptEnd(ptOrigin + vDirection*dParam)
{
}

Line::Line(const Line &Obj):
    Geometry(GEOM_LINE),
    m_ptStart(Obj.m_ptStart),
    m_ptEnd(Obj.m_ptEnd)
{
}

Line::~Line(void)
{
}

Point &Line::StartPoint()
{
    return m_ptStart;
}
Point &Line::EndPoint()
{
    return m_ptEnd;
}

void Line::ModifyLine(Point ptStart, Point ptEnd)
{
    m_ptStart = ptStart;
    m_ptEnd = ptEnd;
}

void Line::ModifyLine(const Line &Obj)
{
    *this = Obj;
}

//Operator Overloading
Line &Line::operator =(const Line &line)
{
    m_ptStart = line.m_ptStart;
    m_ptEnd = line.m_ptEnd;
    
    return *this;
}

Point Line::GetStartPoint()
{
    return m_ptStart;
}

Point Line::GetEndPoint()
{
    return m_ptEnd;
}
