/* Geometry.h geometry

Date        Author      Remark
17-Nov-2013 srinivas    Intail Version
$HISTORY$*/

#include "Geometry.h"


Geometry::Geometry(void):
    m_eGeomType(GEOM), 
    m_uiID((DWID)this)
{
}

Geometry::Geometry(eGeometry eGeomType):
    m_eGeomType(eGeomType),
    m_uiID((DWID)this)
{
}


Geometry::~Geometry(void)
{
}
