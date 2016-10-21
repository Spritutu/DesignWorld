
// DesignWorldAppView.h : interface of the CDesignWorldAppView class
//

#pragma once

#include "GLManager.h"

class CDesignWorldAppView : public CView
{
protected: // create from serialization only
	CDesignWorldAppView();
	DECLARE_DYNCREATE(CDesignWorldAppView)

// Attributes
public:
	CDesignWorldAppDoc* GetDocument() const;

// Operations
public:
    BOOL SetWindowPixelFormat(HDC hDC);
    BOOL CreateViewGLContext(HDC hDC);

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CDesignWorldAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    HGLRC m_hGLContext;

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
    afx_msg void OnSize(UINT nType, int cx, int cy);

    afx_msg void OnViewFront();
    afx_msg void OnViewFit();
    afx_msg void OnViewPan();

private:
    int m_GLPixelIndex;

    CPoint m_currentPoint;
    CPoint m_Startpoint;

    GLManager * m_pGLManager;

};

#ifndef _DEBUG  // debug version in DesignWorldAppView.cpp
inline CDesignWorldAppDoc* CDesignWorldAppView::GetDocument() const
   { return reinterpret_cast<CDesignWorldAppDoc*>(m_pDocument); }
#endif

