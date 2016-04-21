#pragma once
#include "Geometry.h"
#include "Vector.h"
#include "Point.h"

struct str_PLANE
{
    SPoint m_point;
    Vector m_normal;
};

typedef str_PLANE SPlane;

class Plane :
    public Geometry
{
public:
    //classs consturctor
    Plane();
    Plane(const Plane &plane);
    Plane(SPoint point, Vector normal);
    ~Plane();

    void ModifyPlane(Plane plane);
    void ModifyPlane(Point point, Vector normal);

    //operator overloading
    Plane &operator =(const Plane &plane);

private:
    SPoint point();
    Vector normal();
    
private:
    Point m_point;
    Vector m_normal;
};

