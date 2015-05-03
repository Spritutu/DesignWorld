
// DesignWorldAppView.cpp : implementation of the CDesignWorldAppView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "DesignWorldApp.h"
#endif

#include "DesignWorldAppDoc.h"
#include "DesignWorldAppView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDesignWorldAppView

IMPLEMENT_DYNCREATE(CDesignWorldAppView, CView)

BEGIN_MESSAGE_MAP(CDesignWorldAppView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDesignWorldAppView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
    ON_WM_CREATE()
    ON_WM_DESTROY()
    ON_WM_SIZE()
END_MESSAGE_MAP()

// CDesignWorldAppView construction/destruction

CDesignWorldAppView::CDesignWorldAppView()
{
	// TODO: add construction code here
    m_hGLContext = NULL;
    m_pGLManager = GetDWGLManager();

}

CDesignWorldAppView::~CDesignWorldAppView()
{
}

BOOL CDesignWorldAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	//For OpenGL
	cs.style |= (WS_CLIPCHILDREN | WS_CLIPSIBLINGS); 

	return CView::PreCreateWindow(cs);
}

// CDesignWorldAppView drawing

void CDesignWorldAppView::OnDraw(CDC* pDC)
{
	CDesignWorldAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

    m_pGLManager->RenderScene(GL_RENDER);

	// TODO: add draw code for native data here
    SwapBuffers(pDC->m_hDC);
}


// CDesignWorldAppView printing


void CDesignWorldAppView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDesignWorldAppView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDesignWorldAppView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDesignWorldAppView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CDesignWorldAppView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDesignWorldAppView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDesignWorldAppView diagnostics

#ifdef _DEBUG
void CDesignWorldAppView::AssertValid() const
{
	CView::AssertValid();
}

void CDesignWorldAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDesignWorldAppDoc* CDesignWorldAppView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDesignWorldAppDoc)));
	return (CDesignWorldAppDoc*)m_pDocument;
}
#endif //_DEBUG


// CDesignWorldAppView message handlers
BOOL CDesignWorldAppView::SetWindowPixelFormat(HDC hDC)
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

	m_GLPixelIndex = ChoosePixelFormat( hDC, &pixelDesc);
	if (m_GLPixelIndex==0) // Let's choose a default index.
	{
	  m_GLPixelIndex = 1;    
	  if (DescribePixelFormat(hDC, m_GLPixelIndex, 
	  sizeof(PIXELFORMATDESCRIPTOR), &pixelDesc)==0)
	  {
		 return FALSE;
	  }
	}

	if (SetPixelFormat(hDC, m_GLPixelIndex, &pixelDesc)==FALSE)
	{
	  return FALSE;
	}

	return TRUE;;
}

BOOL CDesignWorldAppView::CreateViewGLContext(HDC hDC)
{
	m_hGLContext = wglCreateContext(hDC);
	if (m_hGLContext == NULL)
	{
	  return FALSE;
	}

	if (wglMakeCurrent(hDC, m_hGLContext)==FALSE)
	{
	  return FALSE;
	}

	return TRUE;
}

int CDesignWorldAppView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    HWND hWnd = GetSafeHwnd();
    HDC hDC = ::GetDC(hWnd);

    if( SetWindowPixelFormat(hDC) == FALSE )
        return 0;

    if( CreateViewGLContext( hDC ) == FALSE )
        return 0;

    return 0;
}


void CDesignWorldAppView::OnDestroy()
{
    CView::OnDestroy();

    if( wglGetCurrentContext() != NULL )
    {
        // Make the rendering context not current
        wglMakeCurrent(NULL, NULL);
    }

    if( m_hGLContext != NULL )
    {
        wglDeleteContext(m_hGLContext);
        m_hGLContext = NULL;
    }
    //Now associate DC can be released.
}


void CDesignWorldAppView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);

    m_pGLManager->setWinWidth(cx);
	m_pGLManager->setWinHeight(cy);

	//Creating Global volume(World Coordinate system)
	m_pGLManager->SetViewVolume();
}
