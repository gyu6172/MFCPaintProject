
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

#define RECTANGLEMODE 0
#define CIRCLEMODE 1
#define CURVEMODE 2
#define STARMODE 3
#define SELECTMODE 4


// CChildView

CChildView::CChildView()
{
	m_curMode = 0;
	m_clickPos1 = CPoint(0,0);
	m_clickPos2 = CPoint(0,0);
	m_isMouseDown = false;
	m_isSelected = false;
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

	if (m_curMode == SELECTMODE) {
		if (m_isMouseDown) {
			CPen pen(PS_DOT, 1, RGB(0, 0, 0));
			memDC.SelectObject(pen);
			memDC.SelectStockObject(NULL_BRUSH);
			memDC.Rectangle(m_clickPos1.x, m_clickPos1.y, m_clickPos2.x, m_clickPos2.y);
		}
		for (auto shape : m_selectedShapes.m_group) {
			shape->setBorder(memDC);
		}
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
	if (m_curMode == RECTANGLEMODE) {	//사각형
		CMyShape* shape = new CMyRectangle();
		shape->doMouseDown(point);
		m_pShapes.push_back(shape);
	}
	else if (m_curMode == CIRCLEMODE) {	//원
		CMyShape* shape = new CMyCircle();
		shape->doMouseDown(point);
		m_pShapes.push_back(shape);
	}
	else if (m_curMode == CURVEMODE) {	//곡선
		CMyShape* shape = new CMyCurve();
		shape->doMouseDown(point);
		m_pShapes.push_back(shape);
	}
	else if (m_curMode == STARMODE) {	//별
		CMyShape* shape = new CMyStar();
		shape->doMouseDown(point);
		m_pShapes.push_back(shape);
	}
	else if (m_curMode == SELECTMODE) {	//선택모드
		TRACE("nFlags = %d, MK_SHIFT = %d\n",nFlags, MK_SHIFT);
		m_clickPos1 = CPoint(point);
		m_clickPos2 = CPoint(point);
		for (auto shape : m_pShapes) {
			if (shape->isClicked(point)) {
				m_isSelected = true;
				if (nFlags & MK_SHIFT) {
					m_selectedShapes.addShape(shape);
					Invalidate();
				}
				else {
					m_selectedShapes.clear();
					m_selectedShapes.addShape(shape);
					Invalidate();
				}
			}
		}
		if (!m_isSelected) {
			m_selectedShapes.clear();
			Invalidate();
			m_isMouseDown = true;
		}
	}
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	TRACE("p1=(%d, %d), p2=(%d,%d)\n", m_clickPos1.x, m_clickPos1.y, m_clickPos2.x, m_clickPos2.y);
	if (m_curMode != SELECTMODE) {
		m_pShapes.back()->doMouseUp(point);
		Invalidate();
	}
	else {
		m_clickPos2 = CPoint(point);
		m_isMouseDown = false;
		m_isSelected = false;

		int left = min(m_clickPos1.x, m_clickPos2.x);
		int top = min(m_clickPos1.y, m_clickPos2.y);
		int right = max(m_clickPos1.x, m_clickPos2.x);
		int bottom = max(m_clickPos1.y, m_clickPos2.y);

		for (auto p : m_pShapes) {
			if (p->m_lt.x>left && p->m_lt.y > top && p->m_rb.x < right && p->m_rb.y < bottom) {
				m_selectedShapes.addShape(p);
				m_isSelected = true;
			}
		}
		Invalidate();
	}
	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nFlags & MK_LBUTTON) {
		if (m_curMode != SELECTMODE) {
			m_pShapes.back()->doMouseUp(point);
			Invalidate();
		}
		else {
			if (!m_isSelected) {
				m_clickPos2 = CPoint(point);
				Invalidate();
			}
			else {
				m_clickPos2 = CPoint(point);
				int dx = m_clickPos2.x - m_clickPos1.x;
				int dy = m_clickPos2.y - m_clickPos1.y;
				m_clickPos1 = m_clickPos2;
				m_selectedShapes.move(dx, dy);
				Invalidate();
;			}
		}
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
