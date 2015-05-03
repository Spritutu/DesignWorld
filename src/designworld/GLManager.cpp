/* ObjecManager.cpp designworld

Date        Author              Remark
26-Jan-2014 srinivas            Intail Version
$HISTORY$*/

#include "GLManager.h"
#include "ObjectManager.h"


GLManager::GLManager(void)
{
    m_dScaleFactor = 1.0;
    m_dSphereRad = 1.0;

    m_pObjectManager = GetDWObjectManager();
}


GLManager::~GLManager(void)
{
}

ObjectManager * GLManager::GetObjectManager()
{
    return m_pObjectManager;
}

void GLManager::setWinWidth(int iWinWidth)
{
    m_iWinWidth = iWinWidth;
}

void GLManager::setWinHeight(int iWinHeight)
{
    m_iWinHeight = iWinHeight;
}


// Rendres the scene
void GLManager::RenderScene(GLenum glRenderMode)
{
    ObjectManager *pObjectManager = GetObjectManager();

    static GLdouble white[3] = { 1.0, 1.0, 1.0 };
    // Set up some colors
    static GLdouble red[3] = { 0.8, 0.0, 0.0 };
    static GLdouble green[3] = { 0.0, 0.75, 0.0 };
    static GLdouble purple[3] = { 1.0, 0.14, 0.6667 };


    PrepareScene();

    glPushMatrix();	//push the matrix to create identical matrix with out translation
    //glTranslated(-pObjectManager->m_ViewCenter[0], -pObjectManager->m_ViewCenter[1], -pObjectManager->m_ViewCenter[2]);

    //Render World Coordinate Axes.
    RenderCSYS();

    if (pObjectManager->GetLineCount())
    {
        for (int i = 0; i < pObjectManager->GetLineCount(); i++)
        {
            Line *pLine = pObjectManager->GetLine(i);
            //pLine->Draw();
        }
    }
    //if (pObjectManager->GetBSplineCount())
    //{
    //    for (int i = 0; i < pObjectManager->GetBSplineCount(); i++)
    //    {
    //        CBSpline *pBspline = pObjectManager->GetBSpline(i);
    //        if (glRenderMode == GL_SELECT)
    //            glLoadName(pBspline->GetID());
    //        pBspline->Draw();
    //    }
    //}
    //if (pObjectManager->GetBSurfCount())
    //{
    //    for (int i = 0; i < pObjectManager->GetBSurfCount(); i++)
    //    {
    //        CBSurf *pBSurf = pObjectManager->GetBSurf(i);
    //        if (glRenderMode == GL_SELECT)
    //            glLoadName(pBSurf->GetID());
    //        pBSurf->Draw();
    //    }
    //}
    //if (pObjectManager->GetBeamCount())
    //{
    //    CFemBeam *pBeam = pObjectManager->GetFemBeam(0);
    //    if (glRenderMode == GL_SELECT)
    //        glLoadName(pBeam->GetID());
    //    pBeam->Draw();
    //}

    CreatePolygon();

    glPopMatrix(); //Get Matrix with out translation component
}


void GLManager::PrepareScene()
{
    //// Clear the color and depth buffers
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // use OR run faster on many machines

    glColor3f(1.0, 0.0, 1.0);

    //GLfloat matSpecular[] = {1.0,0.0,0.0,0.0};
    //GLfloat matShininess[] = {250.0};
    //GLfloat lightPosition0[] = {-0.0,0.0,-5.0,0.0};	
    ////GLfloat lightPosition1[] = {0.0,0.0,0.0,0.0};
    //GLfloat sw_Ambient[] = { 0.29f, 0.29f, 0.29f, 1.0f };
    //GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };   

    ////glClearColor(0.0,0.0,0.0,0.0);
    //glShadeModel(GL_SMOOTH);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    //glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
    //glLightfv(GL_LIGHT0, GL_AMBIENT, sw_Ambient);
    //   glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
    //glLightfv(GL_LIGHT0, GL_SPECULAR, matSpecular);
    //glLightfv(GL_LIGHT0, GL_SHININESS, matShininess);	
    //glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);	
    ////glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);	

    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);	
    //glEnable(GL_LIGHT1);

    //         

    //glColor3d(1,0,0);
    //   glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    //   glMaterialfv(GL_FRONT, GL_AMBIENT, sw_Ambient);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    //   glMateriali(GL_FRONT, GL_SHININESS, 400);

    ////glEnable(GL_LIGHT1);	
    glEnable(GL_DEPTH_TEST);
    glLineWidth(0.5);

}

//
//	OutputGlError
//
void GLManager::OutputGlError(char* label)
{
    GLenum errorno = glGetError();
    //if (errorno != GL_NO_ERROR)
        //TRACE("%s had error: #(%d) %s\r\n", label, errorno, gluErrorString(errorno));
}

//-----------------------------------------------------------------------------
// FUNC:	SetViewVolume
// ACTION:	Sets the extents of the view volume. Make sure to MakeCurrent(TRUE)
//			before calling. Call this function if you think you have changed
//			the window extents, part bounding box, or zoom


void GLManager::SetViewVolume()
{
    double sphereSize = m_dSphereRad * 100.0;

    double xextent = double(m_iWinWidth) / min(double(m_iWinWidth), double(m_iWinHeight));
    double yextent = double(m_iWinHeight) / min(double(m_iWinWidth), double(m_iWinHeight));

    glViewport(0, 0, m_iWinWidth, m_iWinHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-xextent * m_dSphereRad * m_dScaleFactor,
        xextent * m_dSphereRad * m_dScaleFactor,
        -yextent * m_dSphereRad * m_dScaleFactor,
        yextent * m_dSphereRad * m_dScaleFactor,
        sphereSize, -sphereSize);
}


//
//Render World Cordinte Axes
//
void GLManager::RenderCSYS()
{
    // Scaling and Ft not effects the Axis length
    double AxsLen = 1.0 * (m_dSphereRad / 10.0) * m_dScaleFactor;

    glColor3d(0.8, 0.0, 0.0);
    glBegin(GL_LINES);//X-axis
    glVertex3d(0, 0, 0); // Vertex Origin
    glVertex3d(AxsLen, 0, 0); // Vertex X
    glEnd();

    glColor3d(0.0, 0.75, 0.0);
    glBegin(GL_LINES);//Y-axis
    glVertex3d(0, 0, 0); // Vertex Origin
    glVertex3d(0, AxsLen, 0); // Vertex Y
    glEnd();

    glColor3d(0.0, 0.0, 0.8);
    glBegin(GL_LINES);//Z-Axis
    glVertex3d(0, 0, 0); // Vertex Origin
    glVertex3d(0, 0, AxsLen); // Vertex Z
    glEnd();
}

//-----------------------------------------------------------------------------
// Helper functions for Pan, Zoom and Rotate
//

//-----------------------------------------------------------------------------
// FUNC;	RotateView
// ACTION:	Rotates the view using the difference between two Points

void GLManager::RotateView(Point point)
{
    //g_streamOut << "Rotation ---------\n";
    //WriteToFile();

    double diffx, diffy;
    //diffx = (double) (TransformDevicePoint(point).x - TransformDevicePoint(m_currentPoint).x);
    //diffy = (double) (TransformDevicePoint(point).y - TransformDevicePoint(m_currentPoint).y);
    diffx = (double)(point.x - m_currentPoint.x);
    diffy = (double)(point.y - m_currentPoint.y);

    m_xRotate = diffx * ROTATE_SENSITIVITY;
    m_yRotate = diffy * ROTATE_SENSITIVITY;

    double m[16];

    glMatrixMode(GL_MODELVIEW);
    glGetDoublev(GL_MODELVIEW_MATRIX, m);
    glLoadIdentity();

    glRotated(m_xRotate, 0.0, 1.0, 0.0);
    glRotated(m_yRotate, 1.0, 0.0, 0.0);

    glMultMatrixd(m);
    //Invalidate(FALSE);

}

//-----------------------------------------------------------------------------
// FUNC:	PanView
// ACTION:	Moves the centre of the view using the difference between two points.

void GLManager::PanView(Point point)
{
    // get the document, manipulating centre 

    double dFactor = PAN_SENSITIVITY * m_dSphereRad * m_dScaleFactor;
    double dPanX = (point.x - m_currentPoint.x) * dFactor;
    double dPanY = (-point.y + m_currentPoint.y) * dFactor;

    double dMat[16] = { 0 };
    VERIFY_GL(glGetDoublev(GL_MODELVIEW_MATRIX, dMat));

    VERIFY_GL(glMatrixMode(GL_MODELVIEW));
    VERIFY_GL(glLoadIdentity());

    VERIFY_GL(glTranslated(dPanX, dPanY, 0.0));

    VERIFY_GL(glMultMatrixd(dMat));

    //Invalidate(FALSE);

    return;
}

//-----------------------------------------------------------------------------
// FUNC:	ZoomView
// ACTION:	Scales up/down the object in the view using the Mouse wheel
//			

void GLManager::ZoomView(double dScale, Point point)
{

    if ((m_dScaleFactor / dScale) > MIN_SCALE_FACTOR)
        m_dScaleFactor /= dScale;

    SetViewVolume();

    //Invalidate(FALSE);

    return;
}

//-----------------------------------------------------------------------------
// FUNC:	ProximitySelect
// ACTION:	Highlight/Selects the proximity entity.
//			
//void GLManager::ProximitySelect( Point point)
//{
//}

////-----------------------------------------------------------------------------
//// FUNC:	ModifyEntity
//// ACTION:	Modify Selected the proximity entity.
////			
//void GLManager::ModifyEntity(Point point)
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

void CreatePolygon()
{
    glPolygonMode(GL_FRONT, GL_LINE);
    glPolygonMode(GL_BACK, GL_LINE);

    glColor3f(0.0, 1.0, 0.0); /* green */

    glBegin(GL_POLYGON);
    glEdgeFlag(GL_TRUE);
    glNormal3d(0.0, 0.0, 1.0);
    glVertex3d(1.0, 0.0, 0.0);
    glVertex3d(2.0, 1.0, 0.0);
    glVertex3d(2.0, 3.0, 0.0);
    glVertex3d(1.0, 2.0, 0.0);
    glVertex3d(0.0, 3.0, 0.0);
    glVertex3d(0.0, 1.0, 0.0);
    glEdgeFlag(GL_FALSE);
    glEnd();

    //glBegin(GL_POLYGON);
    //glColor3f(0.0, 1.0, 0.0); /* green */
    //glVertex3d(0,0,0);
    //glColor3f(1.0, 1.0, 0.0); /* yellow */
    //glVertex3d(1,0,0);
    //glColor3f(1.0, 0.0, 0.0); /* red */
    //glVertex3d(1,1,0);
    //glColor3f(0.0, 0.0, 1.0); /* blue */
    //glVertex3d(0,1,0);
    //glEnd();

    //glFrontFace(GL_CW);
    //glCullFace(GL_BACK);
    //glEnable(GL_CULL_FACE);

    //glBegin(GL_POLYGON);
    //glColor3f(0.0, 1.0, 0.0); /* green */
    //glVertex3d(0,0,0);
    //glColor3f(1.0, 1.0, 0.0); /* yellow */
    //glVertex3d(0,0,-1);
    //glColor3f(1.0, 0.0, 0.0); /* red */
    //glVertex3d(0,1,-1);
    //glColor3f(0.0, 0.0, 1.0); /* blue */
    //glVertex3d(0,1,0);
    //glEnd();

    //glDisable(GL_CULL_FACE);
    //glFrontFace(GL_CCW);
}


DESIGNWORLDAPI GLManager * GetDWGLManager()
{
    GLManager *pObj = new GLManager();

    return pObj;
}