
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "MFW_EngineMFC.h"
#include "ChildView.h" 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "MFW3D_InputMgr.h"

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
	ON_WM_SIZE()
	ON_WM_NCCALCSIZE()
	ON_WM_ENTERSIZEMOVE()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_MOUSEACTIVATE()
	ON_WM_MOUSEHWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);

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
			MFW3D::MFW3D_SceneMgr::GetInstance()->go(&ss2, m_hWnd, rect.Width(), rect.Height());
			SetTimer(1, 20, 0);
		}
		MFW3D::MFW3D_SceneMgr::GetInstance()->getRoot()->renderOneFrame();
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
	
	CWnd::OnClose();
}


void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
}


void CChildView::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// TODO: Add your message handler code here and/or call default
	CRect   rect;
	GetClientRect(&rect);
	//MFW3D::MFW3D_SceneMgr::GetInstance()->ResizeWindow(rect.Width(), rect.Height());
	CWnd::OnNcCalcSize(bCalcValidRects, lpncsp);
}


void CChildView::OnEnterSizeMove()
{
	// TODO: Add your message handler code here and/or call default
	CRect   rect;
	GetClientRect(&rect);
	//MFW3D::MFW3D_SceneMgr::GetInstance()->ResizeWindow(rect.Width(), rect.Height());
	CWnd::OnEnterSizeMove();
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	MFW3D::MouseMotionEvent evt;
	if (oldx == 0 || oldy == 0)
	{
		oldx = point.x;
		oldy = point.y;
	}
	//if (isRote)
	//{
		//evt.state = SDL_PRESSED;
		//evt.x = point.x - oldx;
		//evt.y = point.y - oldy; //point.y;
		//evt.xrel = point.x - oldx; //point.x;
		//evt.yrel = point.y - oldy; //point.y;
	if (isRote)
		evt.state = SDL_PRESSED;
	else
		evt.state = SDL_RELEASED;

	evt.x = point.x;
	evt.y = point.y; //point.y;
	evt.xrel = point.x; //point.x;
	evt.yrel = point.y; //point.y;

	oldx = point.x;
	oldy = point.y;
	MFW3D::MFW3D_SceneMgr::GetInstance()->mouseMoved(evt);
	//}
	CWnd::OnMouseMove(nFlags, point);
}


BOOL CChildView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	MFW3D::KeyboardEvent evt;

	if (nChar + 32 == 'c')
	{
		MFW3D::MFW3D_SceneMgr::GetInstance()->runScene(&ss1);
		return;
	}
	else if (nChar +32 == 'g')
	{
		MFW3D::MFW3D_SceneMgr::GetInstance()->runScene(&ss2);
		return;
	}

	evt.keysym.sym = nChar + 32;
	evt.type = SDL_KEYDOWN;
	evt.repeat = nRepCnt;
	MFW3D::MFW3D_SceneMgr::GetInstance()->keyPressed(evt);

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChildView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	MFW3D::KeyboardEvent evt;
	evt.keysym.sym = nChar + 32;
	evt.type = SDL_KEYUP;
	evt.repeat = nRepCnt;
	MFW3D::MFW3D_SceneMgr::GetInstance()->keyReleased(evt);

	CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}


int CChildView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


void CChildView::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// This feature requires Windows Vista or greater.
	// The symbol _WIN32_WINNT must be >= 0x0600.
	// TODO: Add your message handler code here and/or call default

	CWnd::OnMouseHWheel(nFlags, zDelta, pt);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	isRote = true;
	oldx = point.x;
	oldy = point.y;
	MFW3D::MouseButtonEvent evt;
	evt.button = 0;
	evt.clicks = 1;
	evt.state = SDL_PRESSED;
	evt.x = point.x;
	evt.y = point.y;
	MFW3D::MFW3D_SceneMgr::GetInstance()->mousePressed(evt);
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	isRote = false;
	MFW3D::MouseButtonEvent evt;
	evt.button = 0;
	evt.clicks = 1;
	evt.state = SDL_RELEASED;
	evt.x = point.x;
	evt.y = point.y;
	MFW3D::MFW3D_SceneMgr::GetInstance()->mouseReleased(evt);
	CWnd::OnLButtonUp(nFlags, point);
}


BOOL CChildView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	ShowCursor(FALSE);
	return TRUE; // Ö±½Óreturn
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}


void CChildView::ExitOgre()
{
	MFW3D::MFW3D_SceneMgr::GetInstance()->getRoot()->queueEndRendering();
	//MFW3D::MFW3D_SceneMgr::GetInstance()->closeApp();
}
