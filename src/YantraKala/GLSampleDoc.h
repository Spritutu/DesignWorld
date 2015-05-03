// GLSampleDoc.h : interface of the CGLSampleDoc class
//

#pragma once


class CGLSampleDoc : public CDocument
{
protected: // create from serialization only
	CGLSampleDoc();
	DECLARE_DYNCREATE(CGLSampleDoc)
	
// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CGLSampleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnGeometryLine();
	afx_msg void OnBsplineCurvefair();
	afx_msg void OnBsplineCurvefit();
	afx_msg void OnGeometryBSurface();
	virtual void DeleteContents();
	afx_msg void OnFemBeam();
};


