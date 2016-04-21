#include "Circle.h"


Circle::Circle():
Geometry(GEOM_CIRCLE)
{
}

Circle::Circle(const Circle &circle):
Geometry(GEOM_CIRCLE)
{
    m_point = circle.m_point;
    m_radius = circle.m_radius;
}

Circle::~Circle()
{
}

Circle &Circle::operator=(const Circle &circle)
{
    m_point = circle.m_point;
    m_radius = circle.m_radius;

    return *this;
}

void Circle::ModifyCircle(const Circle &circle)
{
    *this = circle;
}

void Circle::ModifyCircle(Point point, double radius)
{
    m_point = point;
    m_radius = radius;
}

