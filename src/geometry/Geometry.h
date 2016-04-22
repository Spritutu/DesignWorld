#pragma once
/* Geometry.h geometry

Date        Author      Remark
17-Nov-2013 srinivas    Intail Version
$HISTORY$*/

#include <math.h>

typedef unsigned int DWID;

enum 
{
    ONED = 1,
    TWOD,
    THREED,
    FOURD
};

enum eBSplineMethod
{
    BSPLINE_FAIR = 0,
    BSPLINE_FIT,
    BSPLINE_SWEEP
};

enum eBSplineFitMethod
{
    BSPLINE_FIT_UNIFORMSPACE = 0,
    BSPLINE_FIT_CHORDLENGTH,
    BSPLINE_FIT_CENTRIPETAL
};

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

