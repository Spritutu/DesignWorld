/* Line.h geometry

Date        Author      Remark
17-Nov-2013 srinivas    Intail Version
$HISTORY$*/

#pragma once
#include "geometry.h"
#include "Point.h"
#include "Vector.h"

class Line :
    public Geometry
{
public:
    Line(void);
    Line(Point ptStart, Point ptEnd);
    Line(Point ptOrigin, Vector vDirection, double dParam);
    Line(const Line &Obj);
    ~Line(void);

    Point &StartPoint();
    Point &EndPoint();

    void ModifyLine(Point ptStart, Point ptEnd);
    void ModifyLine(const Line &Obj);

    Point GetStartPoint();
    Point GetEndPoint();

    //Operator Overloading
    Line &operator =(const Line &line);

private:
    Point m_ptStart;
    Point m_ptEnd;
};

