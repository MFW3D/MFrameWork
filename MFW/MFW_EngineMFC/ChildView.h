
// ChildView.h : interface of the CChildView class
//


#pragma once

#include "CMyOgreApp.h" 
#include "Scene_Level1.h"
#include "Scene_Mgr.h"
// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:
	CMyOgreApp m_ogreApp;//ogre ÷˜¿‡  
	Scene_Mgr mgr;
	Scene_Level1 ss1;
	bool m_firstDraw;//≥ı¥Œ‰÷»æ  
// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnClose();
};

