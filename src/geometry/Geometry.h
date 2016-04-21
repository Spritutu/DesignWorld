#pragma once
/* Geometry.h geometry

Date        Author      Remark
17-Nov-2013 srinivas    Intail Version
$HISTORY$*/

typedef unsigned int DWID;

enum eGeometry
{
    GEOM = 0,
    GEOM_POINT,
    GEOM_PLANE,
    GEOM_LINE,
    GEOM_CIRCLE,
    GEOM_SPLINE,
    GEOM_SURFACE,
};


class Geometry
{
public:
    Geometry(void);
    Geometry(eGeometry eGeomType);

    virtual ~Geometry(void);

    eGeometry GetType(){ return m_eGeomType; }
    DWID GetID(){ return m_uiID; }

private:

private:
    eGeometry m_eGeomType;
    DWID m_uiID;
};

