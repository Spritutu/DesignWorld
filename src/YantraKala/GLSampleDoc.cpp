// GLSampleDoc.cpp : implementation of the CGLSampleDoc class
//

#include "stdafx.h"

#include "BSplineDlg.h"
#include "FemBeamDlg.h"
#include "GLSampleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGLSampleDoc

IMPLEMENT_DYNCREATE(CGLSampleDoc, CDocument)

BEGIN_MESSAGE_MAP(CGLSampleDoc, CDocument)
	ON_COMMAND(ID_GEOMETRY_LINE, &CGLSampleDoc::OnGeometryLine)
	ON_COMMAND(ID_BSPLINE_CURVEFAIR, &CGLSampleDoc::OnBsplineCurvefair)
	ON_COMMAND(ID_BSPLINE_CURVEFIT, &CGLSampleDoc::OnBsplineCurvefit)
	ON_COMMAND(ID_GEOMETRY_BSURFACE, &CGLSampleDoc::OnGeometryBSurface)
	ON_COMMAND(ID_FEM_BEAM, &CGLSampleDoc::OnFemBeam)
END_MESSAGE_MAP()


// CGLSampleDoc construction/destruction

CGLSampleDoc::CGLSampleDoc()
{
	// TODO: add one-time construction code here
	objLineArray.SetSize( 0, 100 );
	m_dScaleFactor = 1.0;
	m_dSphereRad = 1.0;
	m_bLine = false;

	for(int i = 0; i < 3; i++)
		m_ViewCenter[i] = 0.0;
}

CGLSampleDoc::~CGLSampleDoc()
{
}

BOOL CGLSampleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)


	return TRUE;
}




// CGLSampleDoc serialization

void CGLSampleDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	objLineArray.Serialize( ar );
}


// CGLSampleDoc diagnostics

#ifdef _DEBUG
void CGLSampleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGLSampleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


void CGLSampleDoc::OnGeometryLine()
{
	m_bLine = true;
}

void CGLSampleDoc::OnBsplineCurvefair()
{
    if(m_bLine)
        m_bLine = false;

    static CBSplineDlg cBsplineDlg( this, BSPLINE_FAIR );
	cBsplineDlg.Create( IDD_BSPLINE, NULL );
	
	cBsplineDlg.ShowWindow( SW_SHOW );
}

void CGLSampleDoc::OnBsplineCurvefit()
{
    if(m_bLine)
        m_bLine = false;

	static CBSplineDlg cBsplineDlg( this, BSPLINE_FIT );
	cBsplineDlg.Create( IDD_BSPLINE, NULL );
	cBsplineDlg.ShowWindow( SW_SHOW );
}

void CGLSampleDoc::DeleteContents()
{
	// TODO: Add your specialized code here and/or call the base class
	DeleteLineCounts();
	DeleteBSplineCounts();

	CDocument::DeleteContents();
}

void CGLSampleDoc::OnGeometryBSurface()
{
    if(m_bLine)
        m_bLine = false;

	static CBSplineDlg cBsplineDlg( this, BSPLINE_SWEEP );
	cBsplineDlg.Create( IDD_BSPLINE, NULL );
	
	cBsplineDlg.ShowWindow( SW_SHOW );
}


