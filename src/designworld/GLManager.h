/* ObjecManagert.h designworld

Date        Author      Remark
26-Jan-2014 srinivas    Intail Version
$HISTORY$*/

#pragma once

#include <vector>
#include "dwkernel.h"
#include "Object.h"
#include "DW_Defines.h"
#include "ObjectManager.h"

#include <wtypes.h>
#include <wingdi.h>

//OpenGl Headers
#include <gl\gl.h>
#include <gl\glu.h>


class GLManager
{

public:

    DESIGNWORLDAPI ObjectManager * GetObjectManager();

    //OpenGL operations
    void DESIGNWORLDAPI setWinWidth(int iWinWidth);
    void DESIGNWORLDAPI setWinHeight(int iWinHeight);
    void DESIGNWORLDAPI RenderScene(GLenum glRenderMode);	//OPENGL Render OpenGL scene
    void DESIGNWORLDAPI SetViewVolume();

    void OutputGlError(char* label);		//OPENGL function to display OpenGL errors using TRACE
    void RenderCSYS(void);
    void SetBsplineFit();

    //Pan, Zoom and Rotate
    void DESIGNWORLDAPI RotateView(SPoint point);
    void DESIGNWORLDAPI PanView(SPoint point);
    void DESIGNWORLDAPI ZoomView(double dScale, SPoint point);
    void DESIGNWORLDAPI FrontView();
    void DESIGNWORLDAPI FitView();
    void DESIGNWORLDAPI SetCurrentViewOperation(ParaViewOperation currentOperation);
    ParaViewOperation DESIGNWORLDAPI CurrentViewOperation();

    //Mouse Operation
    SPoint DESIGNWORLDAPI dw_PixlestoPoint(int iX, int iY);
    SPoint DESIGNWORLDAPI dw_PixlestoPoint(SPoint pt);
    void DESIGNWORLDAPI dw_LButtonDown(unsigned int uiFlags, SPoint point);
    void DESIGNWORLDAPI dw_LButtonUp(unsigned int uiFlags, SPoint point);
    
    void DESIGNWORLDAPI dw_setCurrentPoint(SPoint point);
    SPoint DESIGNWORLDAPI dw_getCurrentPoint(SPoint point);

    void PickSquares(SPoint point);
    void ProximitySelect(SPoint point);

    void PrepareScene();

    //Draw
    void DESIGNWORLDAPI DrawLine();

    //command
    void DESIGNWORLDAPI SetGeometryCommand(eGeometryCommand eGeometryCommand);
    eGeometryCommand DESIGNWORLDAPI GetGeometryCommand();

   //Modify entities
    void DESIGNWORLDAPI ModifyEntity(SPoint point);

    GLManager(void);
    virtual ~GLManager(void);

private:

    ParaViewOperation m_currentOperation;

    //Volume Attributes
    double m_dSphereRad; //Volume Radius
    double m_dScaleFactor;

    //Variables
    int m_iWinWidth;
    int m_iWinHeight;
    SPoint m_currentPoint;
    SPoint m_Startpoint;

    GLdouble m_xRotate;
    GLdouble m_yRotate;

    ObjectManager * m_pObjectManager;

    eGeometryCommand m_eGeometryCommand;
};


// Factory function that creates instances of the object.
extern "C" DESIGNWORLDAPI GLManager* GetDWGLManager();

void CreatePolygon();
