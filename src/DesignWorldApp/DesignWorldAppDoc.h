
// DesignWorldAppDoc.h : interface of the CDesignWorldAppDoc class
//


#pragma once

#include "Object.h"
#include "ObjectManager.h"
#include "GLManager.h"

class CDesignWorldAppDoc : public CDocument
{
protected: // create from serialization only
	CDesignWorldAppDoc();
	DECLARE_DYNCREATE(CDesignWorldAppDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CDesignWorldAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

private:
    //CObArray objArray;
};