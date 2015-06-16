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

    ObjectManager * GetObjectManager();

    //OpenGL operations
    void DESIGNWORLDAPI setWinWidth(int iWinWidth);
    void DESIGNWORLDAPI setWinHeight(int iWinHeight);
    void DESIGNWORLDAPI RenderScene(GLenum glRenderMode);	//OPENGL Render OpenGL scene
    void DESIGNWORLDAPI SetViewVolume();

    void OutputGlError(char* label);		//OPENGL function to display OpenGL errors using TRACE
    void RenderCSYS(void);
    void SetBsplineFit();

    //Pan, Zoom and Rotate
    void DESIGNWORLDAPI RotateView(Point point);
    void DESIGNWORLDAPI PanView(Point point);
    void DESIGNWORLDAPI ZoomView(double dScale, Point point);
    void DESIGNWORLDAPI FrontView();

    void PickSquares(Point point);
    void ModifyEntity(Point point);
    void ProximitySelect(Point point);

    void PrepareScene();

    GLManager(void);
    virtual ~GLManager(void);

private:

    //Volume Attributes
    double m_dSphereRad; //Volume Radius
    double m_dScaleFactor;

    //Variables
    int m_iWinWidth;
    int m_iWinHeight;
    Point m_currentPoint;
    Point m_Startpoint;

    GLdouble m_xRotate;
    GLdouble m_yRotate;

    ObjectManager * m_pObjectManager;

};


// Factory function that creates instances of the object.
extern "C" DESIGNWORLDAPI GLManager* GetDWGLManager();

void CreatePolygon();
