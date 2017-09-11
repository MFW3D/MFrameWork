
// MFW_EngineMFC.h : main header file for the MFW_EngineMFC application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFW_EngineMFCApp:
// See MFW_EngineMFC.cpp for the implementation of this class
//

class CMFW_EngineMFCApp : public CWinApp
{
public:
	CMFW_EngineMFCApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFW_EngineMFCApp theApp;
