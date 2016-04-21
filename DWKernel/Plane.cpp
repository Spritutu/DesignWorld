#include "Plane.h"


Plane::Plane(): 
    Geometry(GEOM_PLANE)
{
}

Plane::Plane(const Plane &plane): 
    Geometry(GEOM_PLANE)
{
    m_point = plane.m_point;
    m_normal = plane.m_normal;
}

Plane::Plane(SPoint point, Vector normal):
Geometry(GEOM_PLANE)
{
    m_point = point;
    m_normal = normal;
}

Plane::~Plane()
{
}

Plane &Plane::operator =(const Plane &plane)
{
    m_point = plane.m_point;
    m_normal = plane.m_normal;
    
    return *this;
}

void Plane::ModifyPlane(Plane plane)
{
    *this = plane;
}

void Plane::ModifyPlane(Point point, Vector normal)
{
    m_point = point;
    m_normal = normal;
}

