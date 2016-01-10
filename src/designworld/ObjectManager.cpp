/* ObjecManager.cpp designworld

Date        Author              Remark
26-Jan-2014 srinivas            Intail Version
$HISTORY$*/

#include "ObjectManager.h"
#include "GLManager.h"


ObjectManager::ObjectManager(void)
{
    m_eGeometryCommand = CMD_IDLE;
    m_iCurrentLineID = 0;

    m_uiCurrentID = 0;
}


ObjectManager::~ObjectManager(void)
{
}

void ObjectManager::SetGeometryCommand(eGeometryCommand eGeometryCommand)
{
    m_eGeometryCommand = eGeometryCommand;
}

eGeometryCommand ObjectManager::GetGeometryCommand()
{
    return m_eGeometryCommand;
}
Geometry * ObjectManager::GetGeometry(eGeometry type, int i)
{
    Geometry *pEntity = NULL;

    switch (type)
    {
    case GEOM_POINT:
        pEntity = (Geometry *) m_vecPoints[i];
    case GEOM_LINE:
        pEntity = (Geometry *) m_vecLines[i];
    default:
        break;
    }

    return pEntity;
}

Geometry *ObjectManager::GetGeometry(DWID ID)
{
    Geometry *pEntity = NULL;

    for(int i = 0; i < (int)m_vecPoints.size(); i++)
    {
        pEntity = (Geometry *)m_vecPoints[i];
        if(pEntity->GetID() == ID)
        {
            return pEntity;
        }
    }

    for(int i = 0; i < (int)m_vecLines.size(); i++)
    {
        pEntity = (Geometry *)m_vecLines[i];
        if(pEntity->GetID() == ID)
        {
            return pEntity;
        }
    }

    return NULL;
}

int ObjectManager::GetGeometryCount(eGeometry type)
{
    switch (type)
    {
    case GEOM_POINT:
        return ( int )m_vecPoints.size();
    case GEOM_LINE:
        return ( int )m_vecLines.size();
    default:
        break;
    }
    return 0;
}

void ObjectManager::DeleteGeomtry(eGeometry type)
{
    if( type == GEOM_POINT)
    {
        for(int i = 0; i < (int)m_vecPoints.size(); i++)
            delete m_vecPoints[i];
        m_vecPoints.clear();
    }
    else if(type == GEOM_LINE)
    {
        for(int i = 0; i < (int)m_vecLines.size(); i++)
            delete m_vecLines[i];
        m_vecLines.clear();
    }

}

//Point Implementations
Point *ObjectManager::GetPoint(int i)
{
    return (Point *) m_vecPoints[i];
}

Point *ObjectManager::GetPointFromID(int ID)
{
    int count = GetPointCount();
    if( count ) 
    {
        for(int i = 0; i < count; i++)
        {
            Point* pPoint = (Point*)m_vecPoints[i];
            if(pPoint->GetID() == ID)
            {

                return pPoint;
            }
        }
    }
    return NULL;
}

Point * ObjectManager::CreatePoint(Point pt)
{
    Point *pObject = new Point(pt);

    m_vecPoints.push_back(pObject);

    return pObject;
}

int ObjectManager::GetPointCount()
{
    return ( int )m_vecPoints.size();
}

Point *ObjectManager::AddPoint(Point pt)
{
    Point *pPoint = new Point(pt);

    m_vecPoints.push_back(pPoint);
    //SetModifiedFlag();
    //UpdateAllViews( NULL );
    return pPoint;
}

void ObjectManager::DeletePointCounts()
{
    int count = ( int )m_vecLines.size();

    if(count)
    {
        for(int i = 0; i < (int)count; i++)
            delete m_vecLines[i];

        m_vecLines.clear();
    }
}

//Line Implementation
Line *ObjectManager::GetLine(int i)
{

    Line *pLine = NULL;
    
    if (m_vecLines.size() > 0)
    {
        pLine = m_vecLines[i];
    }

    return pLine;
}

Line *ObjectManager::GetLineFromID(int ID)
{
    int count = GetLineCount();
    if( count ) 
    {
        for(int i = 0; i < count; i++)
        {
            Line* pLine = (Line*)m_vecLines[i];
            if(pLine->GetID() == ID)
            {
                return pLine;
            }
        }
    }
    return NULL;
}

Line *ObjectManager::CreateLine(Point ptFrom, Point ptTo)
{
    Line *pLine = new Line( ptFrom, ptTo );
    //pLine->Draw();
    return pLine;
}

int ObjectManager::GetLineCount()
{
    return ( int )m_vecLines.size();
}

Line *ObjectManager::AddLine(Point ptFrom, Point ptTo)
{
    Line *pLine = new Line( ptFrom, ptTo);

    m_vecLines.push_back(pLine);

    m_iCurrentLineID = pLine->GetID();
    //SetModifiedFlag();
    //UpdateAllViews( NULL );

    return pLine;
}

void ObjectManager::DeleteLineCounts()
{
    int count = ( int )m_vecLines.size();

    if(count)
    {
        for(int i = 0; i < (int)count; i++)
            delete m_vecLines[i];

        m_vecLines.clear();
    }
}

////-----------------------------------------------------------------------------
//// FUNC:	ModifyEntity
//// ACTION:	Modify Selected the proximity entity.
////			
void ObjectManager::ModifyEntity(SPoint point){

    if (m_eGeometryCommand == CMD_LINE){
        Line *pLine = GetLineFromID(m_iCurrentLineID);
        if (pLine != NULL)
            pLine->ModifyLine(pLine->GetStartPoint(), Point(point));
    }
}
//{
//    if (m_iCurrentPointID && m_iPickEntityID)
//    {
//        CGLSampleDoc *pDoc = GetDocument();
//
//        CGeomEntity *pEntity = GetEntityFromID(m_iPickEntityID);
//
//        CGeomPoint *pgptPicked = NULL;
//
//        SetViewVolume();
//        CGeomPoint gpt;
//
//        double dModel[16] = { 0 };
//        double dProj[16] = { 0 };
//        VERIFY_GL(glGetDoublev(GL_MODELVIEW_MATRIX, dModel));
//        VERIFY_GL(glGetDoublev(GL_PROJECTION_MATRIX, dProj));
//
//        GLint glViewPort[4];
//        glGetIntegerv(GL_VIEWPORT, glViewPort);
//        Point glpoint(point.x, glViewPort[3] - point.y);
//
//        if (pEntity->GetGeometryType() == TL_BSPLINE)
//        {
//            CBSpline *pBSpline = (CBSpline*)pEntity;
//
//            int iNumPts = (pBSpline->m_iCtrlPt > pBSpline->m_iDataPt) ? pBSpline->m_iCtrlPt : pBSpline->m_iDataPt;
//
//            for (int i = 0; i < iNumPts; i++)
//            {
//                if (pBSpline->m_iCtrlPt >= iNumPts && pBSpline->m_pgptCtrl[i].GetID() == m_iCurrentPointID)
//                {
//                    GLdouble dlWinPoint[3] = { 0 };
//                    gluProject(pBSpline->m_pgptCtrl[i].m_Coord[0], pBSpline->m_pgptCtrl[i].m_Coord[1], pBSpline->m_pgptCtrl[i].m_Coord[2],
//                        dModel, dProj, glViewPort, &dlWinPoint[0], &dlWinPoint[1], &dlWinPoint[2]);
//
//                    gluUnProject(glpoint.x, glpoint.y, dlWinPoint[2], dModel, dProj, glViewPort, &(gpt.m_Coord[0]), &(gpt.m_Coord[1]), &(gpt.m_Coord[2]));
//                    for (int j = 0; j < 3; j++)
//                        pBSpline->m_pgptCtrl[i].m_Coord[j] = gpt.m_Coord[j];
//
//                    pBSpline->CalculateDataPoints();
//                    break;
//                }
//                else if (pBSpline->m_iDataPt >= iNumPts && pBSpline->m_pgptData[i].GetID() == m_iCurrentPointID)
//                {
//                    GLdouble dlWinPoint[3] = { 0 };
//                    gluProject(pBSpline->m_pgptData[i].m_Coord[0], pBSpline->m_pgptData[i].m_Coord[1], pBSpline->m_pgptData[i].m_Coord[2],
//                        dModel, dProj, glViewPort, &dlWinPoint[0], &dlWinPoint[1], &dlWinPoint[2]);
//
//                    gluUnProject(glpoint.x, glpoint.y, dlWinPoint[2], dModel, dProj, glViewPort, &(gpt.m_Coord[0]), &(gpt.m_Coord[1]), &(gpt.m_Coord[2]));
//                    for (int j = 0; j < 3; j++)
//                        pBSpline->m_pgptData[i].m_Coord[j] = gpt.m_Coord[j];
//                    pBSpline->CalculateControlPoints();
//                    break;
//                }
//            }
//
//            pBSpline->CalculateBSpline();
//        }
//        else if (pEntity->GetGeometryType() == TL_BSURF)
//        {
//            CBSurf *pBSurf = (CBSurf *)pEntity;
//
//            int iNumPts = pBSurf->GetColumnNumber() * pBSurf->GetRowNumber();
//
//            for (int i = 0; i < iNumPts; i++)
//            {
//                if (pBSurf->m_pGeomPts[i].GetID() == m_iCurrentPointID)
//                {
//                    GLdouble dlWinPoint[3] = { 0 };
//                    gluProject(pBSurf->m_pGeomPts[i].m_Coord[0], pBSurf->m_pGeomPts[i].m_Coord[1], pBSurf->m_pGeomPts[i].m_Coord[2],
//                        dModel, dProj, glViewPort, &dlWinPoint[0], &dlWinPoint[1], &dlWinPoint[2]);
//
//                    gluUnProject(glpoint.x, glpoint.y, dlWinPoint[2], dModel, dProj, glViewPort, &(gpt.m_Coord[0]), &(gpt.m_Coord[1]), &(gpt.m_Coord[2]));
//                    for (int j = 0; j < 3; j++)
//                        pBSurf->m_pGeomPts[i].m_Coord[j] = gpt.m_Coord[j];
//                    break;
//                }
//            }
//            pBSurf->CalculateBSurface();
//        }
//    }
//    //Invalidate(FALSE);
//}


/*

// CGLSampleDoc commands


//CBSpline Implementation
CBSpline *CGLSampleDoc::GetBSpline( int i )
{
    if( i < objBSplineArray.GetCount() && i >= 0)
        return ( CBSpline * ) objBSplineArray[i];
    else
        return NULL;
}
CBSpline *CGLSampleDoc::GetBSplineFromID(int ID)
{
    int count = GetBSplineCount();
    if( count ) 
    {
        for(int i = 0; i < count; i++)
        {
            CBSpline* pBspline = (CBSpline*)objBSplineArray[i];
            if(pBspline->GetID() == ID)
            {
                return pBspline;
            }
        }
    }
    return NULL;
}
int CGLSampleDoc::GetBSplineCount()
{
    return ( int )objBSplineArray.GetSize();
}
CBSpline *CGLSampleDoc::CreateBSpline( int nCtrlPt, int iOrder, int nSpanPt,  Point *pCtrlPt )
{
    CGeomPoint *pdCtrlPt = new CGeomPoint[nCtrlPt];
    for( int i = 0; i < nCtrlPt; i++ )
        pdCtrlPt[i] = CGeomPoint::CptToGeomPt( pCtrlPt[i] );

    double *pKnotVec = new double[nCtrlPt+iOrder];
    OpenUniformKnotVector( nCtrlPt, iOrder, pKnotVec, false );

    CBSpline *pBSpline = new CBSpline( nCtrlPt, iOrder, nSpanPt, NULL, pKnotVec, pdCtrlPt, RGB(255,255,255) );
    pBSpline->Draw();
    return pBSpline;
}
CBSpline *CGLSampleDoc::AddBSpline( int nCtrlPt, int iOrder, int nSpanPt, double *pdParamRange, double *pdKnotVec, CGeomPoint *pdCtrlPt, COLORREF clrCurveColor )
{
    CBSpline *pBSpline = new CBSpline( nCtrlPt, iOrder, nSpanPt, pdParamRange, pdKnotVec, pdCtrlPt, clrCurveColor );

    objBSplineArray.Add( pBSpline );
    SetModifiedFlag();
    UpdateAllViews( NULL );
    return pBSpline;
}
CBSpline *CGLSampleDoc::AddBSpline( int nCtrlPt, int iOrder, int nSpanPt, int nDataPt, eBSplineFitMethod methodBsplineFit, double *pdParamRange, double *pdKnotVec, CGeomPoint *pgptData, COLORREF clrCurveColor )
{
    CBSpline *pBSpline = new CBSpline( nCtrlPt, iOrder, nSpanPt, nDataPt, methodBsplineFit, pdParamRange, pdKnotVec, pgptData, clrCurveColor );

    objBSplineArray.Add( pBSpline );
    SetModifiedFlag();
    UpdateAllViews( NULL );
    return pBSpline;
}
void CGLSampleDoc::DeleteBSplineCounts()
{
    int count = GetBSplineCount();
    if( count ) 
    {
        for( int i = 0; i < count; i++ )
            delete objBSplineArray[i];
        objBSplineArray.RemoveAll();
    }
}

void CGLSampleDoc::DeleteBspline(int ID)
{
    int count = GetBSplineCount();
    if( count ) 
    {
        for(int i = 0; i < count; i++)
        {
            CBSpline* pBspline = (CBSpline*)objBSplineArray[i];

            if(pBspline->GetID() == ID)
            {
                delete objBSplineArray[i];
                objBSplineArray.RemoveAt(i);
                return;
            }
        }
    }
}

bool CGLSampleDoc::ValidateBSplineID(int ID)
{
    int count = GetBSplineCount();
    if( count ) 
    {
        for(int i = 0; i < count; i++)
        {
            CBSpline* pBspline = (CBSpline*)objBSplineArray[i];

            if(pBspline->GetID() == ID)
            {
                return true;
            }
        }
    }
    return false;
}

//BSurface operations Implementation
CBSurf *CGLSampleDoc::GetBSurf(int i)
{
    if( i < objBsurfArray.GetCount() && i >= 0)
        return ( CBSurf * ) objBsurfArray[i];
    else
        return NULL;
}
CBSurf *CGLSampleDoc::GetBSurfFromID(int ID)
{
    int count = GetBSurfCount();
    if( count ) 
    {
        for(int i = 0; i < count; i++)
        {
            CBSurf* pBSurf = (CBSurf*)objBsurfArray[i];
            if(pBSurf->GetID() == ID)
            {
                return pBSurf;
            }
        }
    }
    return NULL;
}

int CGLSampleDoc::GetBSurfCount()
{
    return ( int )objBsurfArray.GetSize();
}

CBSurf *CGLSampleDoc::AddBSurf(CBSpline *pUBSpline, CBSpline *pVBSpline)
{
    CBSurf *pBSurf = new CBSurf(pUBSpline, pVBSpline);

    objBsurfArray.Add(pBSurf);
    SetModifiedFlag();
    UpdateAllViews( NULL );
    return pBSurf;
}

CBSurf *CGLSampleDoc::AddBSurf(CGeomPoint *pGeomPt, int iUPts, int iVPts, int iUSpan, int iVSpan)
{
    CBSurf *pBSurf = new CBSurf(pGeomPt, iUPts, iVPts, iUSpan, iVSpan);

    objBsurfArray.Add(pBSurf);
    SetModifiedFlag();
    UpdateAllViews( NULL );
    return pBSurf;
}

void CGLSampleDoc::DleteBSurf(int ID)
{
    int count = GetBSurfCount();
    if( count ) 
    {
        for(int i = 0; i < count; i++)
        {
            CBSurf* pBSurf = (CBSurf*)objBsurfArray[i];

            if(pBSurf->GetID() == ID)
            {
                delete objBsurfArray[i];
                objBsurfArray.RemoveAt(i);
                return;
            }
        }
    }
}

bool CGLSampleDoc::ValidateBSurfID(int ID)
{
    int count = GetBSurfCount();
    if( count ) 
    {
        for(int i = 0; i < count; i++)
        {
            CBSurf* pBSurf = (CBSurf*)objBsurfArray[i];

            if(pBSurf->GetID() == ID)
            {
                return true;
            }
        }
    }
    return false;
}


void CGLSampleDoc::OnFemBeam()
{
    if(m_bLine)
        m_bLine = false;

    static CFemBeamDlg cFemBeamDlg( this );
    cFemBeamDlg.Create( IDD_FEM_BEAM, NULL );

    cFemBeamDlg.ShowWindow( SW_SHOW );
}

CFemBeam *CGLSampleDoc::GetFemBeam(int i)
{
    if( i < objFemBeamArray.GetCount() && i >= 0)
        return ( CFemBeam * ) objFemBeamArray[i];
    else
        return NULL;
}
CFemBeam *CGLSampleDoc::GetFemBeamID(int ID)
{
    int count = GetBeamCount();
    if( count ) 
    {
        for(int i = 0; i < count; i++)
        {
            CFemBeam* pFemBeam = (CFemBeam*)objFemBeamArray[i];
            if(pFemBeam->GetID() == ID)
            {
                return pFemBeam;
            }
        }
    }
    return NULL;
}

int CGLSampleDoc::GetBeamCount()
{
    return ( int )objFemBeamArray.GetSize();
}

CFemBeam *CGLSampleDoc::AddBeam(double dBeamLength, int iBeamNodes, double dYModuli, double dSectionArea, CGeomPoint *pgptEndPoints)
{
    CFemBeam *pFemBeam = new CFemBeam( dBeamLength, iBeamNodes, dYModuli, dSectionArea, pgptEndPoints );

    objFemBeamArray.Add( pFemBeam );
    SetModifiedFlag();
    UpdateAllViews( NULL );
    return pFemBeam;
}

void CGLSampleDoc::deleteFemBeam(int ID)
{
    int count = GetBSurfCount();
    if( count ) 
    {
        for(int i = 0; i < count; i++)
        {
            CFemBeam* pBeam = (CFemBeam*)objFemBeamArray[i];

            if(pBeam->GetID() == ID)
            {
                delete objFemBeamArray[i];
                objFemBeamArray.RemoveAt(i);
                return;
            }
        }
    }
}

bool CGLSampleDoc::ValidateFemBeamID(int ID)
{
    int count = GetBSurfCount();
    if( count ) 
    {
        for(int i = 0; i < count; i++)
        {
            CFemBeam* pBeam = (CFemBeam*)objFemBeamArray[i];

            if(pBeam->GetID() == ID)
            {
                return true;
            }
        }
    }
    return false;
}
*/

ObjectManager * GetDWObjectManager()
{
    ObjectManager *pObj = new ObjectManager;

    return pObj;
}
