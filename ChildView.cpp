
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MFCPaintProject.h"
#include "ChildView.h"
#include "CMyShape.h"
#include "CMyRectangle.h"
#include "CMyCircle.h"
#include "CMyCurve.h"
#include "CMyStar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_curMode = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_RECTANGLE, &CChildView::OnRectangle)
	ON_COMMAND(ID_CIRCLE, &CChildView::OnCircle)
	ON_COMMAND(ID_CURVE, &CChildView::OnCurve)
	ON_COMMAND(ID_STAR, &CChildView::OnStar)
	ON_COMMAND(ID_SELECT, &CChildView::OnSelect)
	ON_COMMAND(ID_GROUP, &CChildView::OnGroup)
	ON_COMMAND(ID_UNGROUP, &CChildView::OnUngroup)
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	CRect rect;
	GetClientRect(rect);

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	memDC.SelectObject(bitmap);
	memDC.Rectangle(rect);

	CString str;
	str.Format(_T("Number of Shapes : %d"), m_pShapes.size());
	memDC.TextOutW(0, 0, str);

	//여기다가 그리기
	for (int i = 0; i < m_pShapes.size(); i++) {
		m_pShapes[i]->draw(memDC);
	}


	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
}



BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return true;
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_curMode == 0) {	//사각형
		CMyShape* shape = new CMyRectangle();
		shape->doMouseDown(point);
		m_pShapes.push_back(shape);
	}
	else if (m_curMode == 1) {	//원
		CMyShape* shape = new CMyCircle();
		shape->doMouseDown(point);
		m_pShapes.push_back(shape);
	}
	else if (m_curMode == 2) {	//곡선
		CMyShape* shape = new CMyCurve();
		shape->doMouseDown(point);
		m_pShapes.push_back(shape);
	}
	else if (m_curMode == 3) {	//별
		CMyShape* shape = new CMyStar();
		shape->doMouseDown(point);
		m_pShapes.push_back(shape);
	}
	else if (m_curMode == 4) {	//선택모드
		
	}
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_pShapes.back()->doMouseUp(point);
	Invalidate();
	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nFlags == MK_LBUTTON) {
		m_pShapes.back()->doMouseUp(point);
		Invalidate();
	}

	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnRectangle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_curMode = 0;
}


void CChildView::OnCircle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_curMode = 1;
}


void CChildView::OnCurve()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_curMode = 2;
}


void CChildView::OnStar()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_curMode = 3;

}


void CChildView::OnSelect()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_curMode = 4;
}


void CChildView::OnGroup()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CChildView::OnUngroup()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
