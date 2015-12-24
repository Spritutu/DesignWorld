/* ObjecManagert.h designworld

Date        Author      Remark
26-Jan-2014 srinivas    Intail Version
$HISTORY$*/

#pragma once

#include <vector>
#include "dwkernel.h"
#include "Object.h"
#include "DW_Defines.h"

class ObjectManager
{

/*
    // Attributes
public:
    CObArray objLineArray;
    CObArray objBSplineArray;
    CObArray objBsurfArray;
    CObArray objFemBeamArray;

    //Volume Attributes
    double m_dSphereRad; //Volume Radius
    double m_dScaleFactor;

    GLdouble m_ViewCenter[3];

    //Flags
    bool m_currentFlag;

    // Operations
public:

    CGeomEntity *GetEntityFromID(int ID);
    
    //BSpline operations
    CBSpline *GetBSpline( int i );
    CBSpline *GetBSplineFromID(int ID);
    int GetBSplineCount();
    CBSpline *CreateBSpline( int nCtrlPt, int iOrder, int nSpanPt,  Point *pCtrlPt );
    CBSpline *AddBSpline( int nCtrlPt, int iOrder, int nSpanPt, double *pdParamRange, double *pdKnotVec, CGeomPoint *pdCtrlPt, COLORREF clrCurveColor );
    CBSpline *AddBSpline( int nCtrlPt, int iOrder, int nSpanPt, int nDataPt, eBSplineFitMethod methodBsplineFit, double *pdParamRange, double *pdKnotVec, CGeomPoint *pgptData, COLORREF clrCurveColor );
    void DeleteBSplineCounts();
    void DeleteBspline(int ID);
    bool ValidateBSplineID(int ID);

    //BSurface operations
    CBSurf *GetBSurf(int i);
    CBSurf *GetBSurfFromID(int ID);
    int GetBSurfCount();
    CBSurf *AddBSurf(CBSpline *pUBSpline, CBSpline *pVBSpline);
    CBSurf *AddBSurf(CGeomPoint *pGeomPt, int iRow, int iColumn, int iUSpan, int iVSpan);
    void DleteBSurf(int ID);
    bool ValidateBSurfID(int ID);

    //Fem Beam Operations
    //Add one Beam at a time.
    CFemBeam *GetFemBeam(int i);
    CFemBeam *GetFemBeamID(int ID);
    int GetBeamCount();
    CFemBeam *AddBeam(double dBeamLength, int iBeamNodes, double dYModuli, double dSectionArea, CGeomPoint *pgptEndPoints);
    void deleteFemBeam(int ID);
    bool ValidateFemBeamID(int ID);
*/

public:
    ObjectManager(void);
    ~ObjectManager(void);

    //Geometry Operations
    Geometry * GetGeometry(eGeometry type, int i);
    Geometry * GetGeometry( DWID ID);
    int GetGeometryCount(eGeometry type);
    void DeleteGeomtry(eGeometry type);

    //Point operations
    Point *GetPoint(int i);
    Point *GetPointFromID(int ID);
    Point * CreatePoint(Point pt);
    int GetPointCount();
    Point *AddPoint(Point pt);
    void DeletePointCounts();

    //Line operations
    Line *GetLine(int i);
    Line *GetLineFromID(int ID);
    Line *CreateLine(Point ptFrom, Point ptTo);
    int GetLineCount();
    Line *AddLine(Point ptFrom, Point ptTo);
    void DeleteLineCounts();
    
    //Modify entities
    void DESIGNWORLDAPI ModifyEntity(SPoint point);

private:
    std::vector<Line *> m_vecLines;
    std::vector<Point *> m_vecPoints;
    unsigned int m_uiCurrentID;

public:
    bool m_bLine;
    unsigned int m_iCurrentLineID;
};


// Factory function that creates instances of the object.
extern "C" DESIGNWORLDAPI ObjectManager* GetDWObjectManager();
