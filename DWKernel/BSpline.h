#pragma once
#include "Geometry.h"
#include "Matrix.h"
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
    
    SPoint *m_pgptCtrl;
    SPoint *m_pgptCurve;
    SPoint *m_pgptData;
    double *m_pdKnotVec;
    double m_dParamRange[2];
    SPoint m_gptCentre;
};

void bspline_i(int nCtrlPt, int iOrder, int nSpanPt, double *pdKontVec, SPoint *pdCtrlPt, SPoint *pdCurvePt, int &iCurvePt);
void BSplineBlends(double dParam, int iCtrlPt, int iOrder, double *pdKontVec, double *pdBSplnBlends);
void BSplineBlends_1(double dParam, int iCtrlPt, int iOrder, double *pdKontVec, double *pdBSplnBlends);
void BSplineBlends_2(double dParam, int iCtrlPt, int iOrder, double *pdKontVec, double *pdBSplnBlends, int iDervs, double **pdBlendDervs);
void OpenUniformKnotVector(int nCtrlPt, int iOrder, double *pdKontVec, bool bNorm = false);
void PeriodicKnotVector(int nCtrlPt, int iOrder, double *pdKontVec, bool bNorm = false);
int IsPeriodic(int iCtrlPt, int iOrder, double *pdKnotVec);
void GetBSplineKnotPoints(int iCtrlPt, int iOrder, double  *pdKnotVec, SPoint *pgptCtrlPt, SPoint *pgptKnotPt);
void BSpline_btParam(int iCtrlPt, int iOrder, int iSpanPt, double *pdParamRange, double *pdKontVec, SPoint *pgptCtrl, SPoint *pgptCurve, int &iCurvePt);
void FindMinMax(double *pdArr, int iSize, double &dMaxValue, double &dMinValue);
void BSplineFit(int nCtrlPt, int iOrder, double *pdParamRange, double *pdKontVec, int nDataPt, eBSplineFitMethod methodBsplineFit, SPoint *pgptData, SPoint *pgptCtrl);
void BSplineFitEndTangents(int nCtrlPt, int iOrder, double *pdParamRange, double *pdKontVec, int nDataPt, Vector *pFirstDerivatives, eBSplineFitMethod methodBsplineFit, SPoint *pgptData, SPoint *pgptCtrl);
void BSplineFirstDervativeBlends(double dParam, int iCtrlPt, int iOrder, double *pdKontVec, double *pdDerivativeBlends);
void BSplineFirstDervativeAtParam(double dParam, int iCtrlPt, int iOrder, double *pdKontVec, SPoint *pdCtrlPt, double *pdVector);
void BSplineSecondDervativeBlends(double dParam, int iCtrlPt, int iOrder, double *pdKontVec, double *pdDerivativeBlends);
void BSplineSecondDervativeAtParam(double dParam, int iCtrlPt, int iOrder, double *pdKontVec, SPoint *pdCtrlPt, double *pdVector);
void ParameterAssignment(int nCtrlPt, int iOrder, int nDataPt, eBSplineFitMethod methodBsplineFit, SPoint *pgptData, double *pParameters);
void GetBSplineDataPoints(int iCtrlPt, int iOrder, double *pdParamRange, double  *pdKnotVec, eBSplineFitMethod methodBsplineFit, SPoint *pgptCtrlPt, SPoint *pgptDataPt);




