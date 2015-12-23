
// DWMFCApplication.h : main header file for the DWMFCApplication application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "Resource.h"// main symbols


// CDWMFCApplicationApp:
// See DWMFCApplication.cpp for the implementation of this class
//

class CDWMFCApplicationApp : public CWinApp
{
public:
	CDWMFCApplicationApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDWMFCApplicationApp theApp;
