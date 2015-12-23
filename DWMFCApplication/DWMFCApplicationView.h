
// DWMFCApplicationView.h : interface of the CDWMFCApplicationView class
//

#pragma once

#include "GLManager.h"

class CDWMFCApplicationView : public CView
{
protected: // create from serialization only
	CDWMFCApplicationView();
	DECLARE_DYNCREATE(CDWMFCApplicationView)

// Attributes
public:
	CDWMFCApplicationDoc* GetDocument() const;

// Operations
public:
    BOOL SetWindowPixelFormat(HDC hDC);
    BOOL CreateViewGLContext(HDC hDC);

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CDWMFCApplicationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

private:
    HGLRC m_hGLContext;
    int m_GLPixelIndex;

    CPoint m_currentPoint;
    CPoint m_Startpoint;

    GLManager * m_pGLManager;

public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
    afx_msg void OnViewFront();
    afx_msg void OnViewFit();
    afx_msg void OnViewPan();
    afx_msg void OnGeometryLine();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in DWMFCApplicationView.cpp
inline CDWMFCApplicationDoc* CDWMFCApplicationView::GetDocument() const
   { return reinterpret_cast<CDWMFCApplicationDoc*>(m_pDocument); }
#endif

