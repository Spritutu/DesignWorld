#pragma once
#include "Geometry.h"
#include "Point.h"
#include "Vector.h"

struct str_CIRCLE
{
    SPoint m_point;
    double m_radius;

    str_CIRCLE(SPoint point, double radius)
    {
        m_point = point;
        m_radius = radius;
    }
};

typedef str_CIRCLE SCircle;

class Circle :
    public Geometry
{
public:
    Circle();
    Circle(const Circle &circle);
    Circle(Point point, double radius);
    ~Circle();

    void ModifyCircle(const Circle &circle);
    void ModifyCircle(Point point, double radius);

    //Operator Overloading
    Circle &operator =(const Circle &circle);
private:
    Point m_point;
    double m_radius;
};

