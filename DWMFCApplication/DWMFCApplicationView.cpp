
// DWMFCApplicationView.cpp : implementation of the CDWMFCApplicationView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "DWMFCApplication.h"
#endif

#include "DWMFCApplicationDoc.h"
#include "DWMFCApplicationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDWMFCApplicationView

IMPLEMENT_DYNCREATE(CDWMFCApplicationView, CView)

BEGIN_MESSAGE_MAP(CDWMFCApplicationView, CView)
    ON_WM_CREATE()
    ON_WM_DESTROY()
    ON_WM_SIZE()
    ON_COMMAND(ID_VIEW_FRONT, &CDWMFCApplicationView::OnViewFront)
    ON_COMMAND(ID_VIEW_FIT, &CDWMFCApplicationView::OnViewFit)
    ON_COMMAND(ID_VIEW_PAN, &CDWMFCApplicationView::OnViewPan)
    ON_COMMAND(ID_GEOMETRY_LINE, &CDWMFCApplicationView::OnGeometryLine)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CDWMFCApplicationView construction/destruction

CDWMFCApplicationView::CDWMFCApplicationView()
{
    m_hGLContext = NULL;
    m_pGLManager = GetDWGLManager();
}

CDWMFCApplicationView::~CDWMFCApplicationView()
{
}

BOOL CDWMFCApplicationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
    //For OpenGL
    cs.style |= (WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

	return CView::PreCreateWindow(cs);
}

// CDWMFCApplicationView drawing

void CDWMFCApplicationView::OnDraw(CDC* pDC)
{
	CDWMFCApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
    m_pGLManager->RenderScene(GL_RENDER);
    SwapBuffers(pDC->m_hDC);
}


// CDWMFCApplicationView diagnostics

#ifdef _DEBUG
void CDWMFCApplicationView::AssertValid() const
{
	CView::AssertValid();
}

void CDWMFCApplicationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDWMFCApplicationDoc* CDWMFCApplicationView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDWMFCApplicationDoc)));
	return (CDWMFCApplicationDoc*)m_pDocument;
}
#endif //_DEBUG

// Operations
BOOL CDWMFCApplicationView::SetWindowPixelFormat(HDC hDC)
{
    PIXELFORMATDESCRIPTOR pixelDesc;
    pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pixelDesc.nVersion = 1;
    pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW |
        PFD_DOUBLEBUFFER |
        PFD_SUPPORT_OPENGL |
        PFD_STEREO_DONTCARE;
    pixelDesc.iPixelType = PFD_TYPE_RGBA;
    pixelDesc.cColorBits = 32;
    pixelDesc.cRedBits = 8;
    pixelDesc.cRedShift = 16;
    pixelDesc.cGreenBits = 8;
    pixelDesc.cGreenShift = 8;
    pixelDesc.cBlueBits = 8;
    pixelDesc.cBlueShift = 0;
    pixelDesc.cAlphaBits = 0;
    pixelDesc.cAlphaShift = 0;
    pixelDesc.cAccumBits = 64;
    pixelDesc.cAccumRedBits = 16;
    pixelDesc.cAccumGreenBits = 16;
    pixelDesc.cAccumBlueBits = 16;
    pixelDesc.cAccumAlphaBits = 0;
    pixelDesc.cDepthBits = 32;
    pixelDesc.cStencilBits = 8;
    pixelDesc.cAuxBuffers = 0;
    pixelDesc.iLayerType = PFD_MAIN_PLANE;
    pixelDesc.bReserved = 0;
    pixelDesc.dwLayerMask = 0;
    pixelDesc.dwVisibleMask = 0;
    pixelDesc.dwDamageMask = 0;

    m_GLPixelIndex = ChoosePixelFormat(hDC, &pixelDesc);
    if (m_GLPixelIndex == 0) // Let's choose a default index.
    {
        m_GLPixelIndex = 1;
        if (DescribePixelFormat(hDC, m_GLPixelIndex,
            sizeof(PIXELFORMATDESCRIPTOR), &pixelDesc) == 0)
        {
            return FALSE;
        }
    }

    if (SetPixelFormat(hDC, m_GLPixelIndex, &pixelDesc) == FALSE)
    {
        return FALSE;
    }

    return TRUE;;
}

BOOL CDWMFCApplicationView::CreateViewGLContext(HDC hDC)
{
    m_hGLContext = wglCreateContext(hDC);
    if (m_hGLContext == NULL)
    {
        return FALSE;
    }

    if (wglMakeCurrent(hDC, m_hGLContext) == FALSE)
    {
        return FALSE;
    }

    return TRUE;
}

// CDWMFCApplicationView message handlers



int CDWMFCApplicationView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    HWND hWnd = GetSafeHwnd();
    HDC hDC = ::GetDC(hWnd);

    if (SetWindowPixelFormat(hDC) == FALSE)
        return 0;

    if (CreateViewGLContext(hDC) == FALSE)
        return 0;

    return 0;
}


void CDWMFCApplicationView::OnDestroy()
{
    CView::OnDestroy();

    if (wglGetCurrentContext() != NULL)
    {
        // Make the rendering context not current
        wglMakeCurrent(NULL, NULL);
    }

    if (m_hGLContext != NULL)
    {
        wglDeleteContext(m_hGLContext);
        m_hGLContext = NULL;
    }
    //Now associate DC can be released.
}


void CDWMFCApplicationView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);

    m_pGLManager->setWinWidth(cx);
    m_pGLManager->setWinHeight(cy);

    //Creating Global volume(World Coordinate system)
    m_pGLManager->SetViewVolume();
}


void CDWMFCApplicationView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
    // TODO: Add your specialized code here and/or call the base class
    Invalidate(false);
}

void CDWMFCApplicationView::OnViewFront()
{
    // TODO: Add your command handler code here

    m_pGLManager->FrontView();

    Invalidate(FALSE);
}

void CDWMFCApplicationView::OnViewFit()
{
    // TODO: Add your command handler code here
    m_pGLManager->FitView();

    Invalidate(FALSE);
}

void CDWMFCApplicationView::OnViewPan()
{
    m_pGLManager->SetCurrentViewOperation(Pan);

    Invalidate(FALSE);
}


void CDWMFCApplicationView::OnGeometryLine()
{
    m_pGLManager->m_bLine = true;
}


void CDWMFCApplicationView::OnLButtonDown(UINT nFlags, CPoint point)
{
    Invalidate(FALSE);

    m_pGLManager->dw_LButtonDown(nFlags, m_pGLManager->dw_PixlestoPoint(point.x, point.y));

    CView::OnLButtonDown(nFlags, point);
}


void CDWMFCApplicationView::OnLButtonUp(UINT nFlags, CPoint point)
{
    m_pGLManager->dw_LButtonUp(nFlags, m_pGLManager->dw_PixlestoPoint(point.x, point.y));

    Invalidate(FALSE);

    CView::OnLButtonUp(nFlags, point);
}

void CDWMFCApplicationView::OnMouseMove(UINT nFlags, CPoint point)
{
    CView::OnMouseMove(nFlags, point);

    SPoint pt = m_pGLManager->dw_PixlestoPoint(point.x, point.y);

    if (nFlags == MK_MBUTTON)
    {
        m_pGLManager->RotateView( pt );
    }

    if (nFlags)
    {
        switch (m_pGLManager->CurrentViewOperation())
        {
            //case Rotate :
            //m_pGLManager->RotateView( pt );
            //	break;
        case Pan:
            m_pGLManager->PanView( pt );
            break;
        case Zoom:
            //m_pGLManager->ZoomView( pt );
            break;
        case Idle:
            //m_pGLManager->ProximitySelect( pt );
            break;
        case Pick:
            m_pGLManager->ModifyEntity( pt );
        default:
            break;
        }
    }

    m_currentPoint = point;

    if (m_pGLManager->m_bLine && m_pGLManager->m_iCurrentLineID)
    {
        m_pGLManager->ModifyLine(pt);

        Invalidate(FALSE);
    }
}
