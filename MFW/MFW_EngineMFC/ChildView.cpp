
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "MFW_EngineMFC.h"
#include "ChildView.h" 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_CLOSE()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	try {
		if (m_firstDraw)
		{
			m_firstDraw = false;
			CRect   rect;
			GetClientRect(&rect);
			//m_ogreApp.go(rect, m_hWnd);//传入MFC主窗口句柄  
			mgr.go(&ss1, m_hWnd, rect.Width(), rect.Height());
			SetTimer(1, 20, 0);
		}
		mgr.getRoot()->renderOneFrame();
		//m_ogreApp.getRoot()->renderOneFrame();
	}
	catch (Ogre::Exception& e) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32  
#else  
		std::cerr << "An exception has occured: " <<
			e.getFullDescription().c_str() << std::endl;
#endif  
	}
	// Do not call CWnd::OnPaint() for painting messages
}



void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (1 == nIDEvent)
	{
		m_ogreApp.getRoot()->renderOneFrame();
	}
	CWnd::OnTimer(nIDEvent);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CWnd::OnEraseBkgnd(pDC);
}


void CChildView::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	mgr.closeApp();
	CWnd::OnClose();
}
