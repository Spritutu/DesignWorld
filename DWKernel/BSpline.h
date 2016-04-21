#pragma once
#include "Geometry.h"
#include "Point.h"
#include "Vector.h"

class BSpline :
    public Geometry
{
public:
    BSpline();
    ~BSpline();

private:
    int	m_iCtrlPt;
    int m_iOrder;
    int m_iDegree;
    int m_iSpanPt;
    int m_iCurvePts;
    int m_iDataPt;
    
    Point *m_pgptCtrl;
    Point *m_pgptCurve;
    Point *m_pgptData;
    double *m_pdKnotVec;
    double m_dParamRange[2];
    Point m_gptCentre;
};

