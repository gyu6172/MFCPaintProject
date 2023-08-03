
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
	ON_COMMAND(ID_BRINGFRONT, &CChildView::OnBringfront)
	ON_COMMAND(ID_BRINGBACK, &CChildView::OnBringback)
	ON_UPDATE_COMMAND_UI(ID_RECTANGLE, &CChildView::OnUpdateRectangle)
	ON_UPDATE_COMMAND_UI(ID_SELECT, &CChildView::OnUpdateSelect)
	ON_UPDATE_COMMAND_UI(ID_CURVE, &CChildView::OnUpdateCurve)
	ON_UPDATE_COMMAND_UI(ID_CIRCLE, &CChildView::OnUpdateCircle)
	ON_UPDATE_COMMAND_UI(ID_GROUP, &CChildView::OnUpdateGroup)
	ON_UPDATE_COMMAND_UI(ID_UNGROUP, &CChildView::OnUpdateUngroup)
	ON_UPDATE_COMMAND_UI(ID_BRINGFRONT, &CChildView::OnUpdateBringfront)
	ON_UPDATE_COMMAND_UI(ID_BRINGBACK, &CChildView::OnUpdateBringback)
	ON_WM_CONTEXTMENU()
	ON_WM_KEYDOWN()
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
	str.Format(_T("Number of Shapes : %d"), m_pShapes.GetSize());
	memDC.TextOutW(0, 0, str);

	CString str1;
	str1.Format(_T("Number of Selected : %d"), m_selectedShapes.m_group.GetSize());
	memDC.TextOutW(0, 20, str1);

	//여기다가 그리기
	POSITION pos = m_pShapes.GetHeadPosition();
	while (pos != NULL) {
		m_pShapes.GetNext(pos)->draw(memDC);
	}

	if (m_curMode == SELECTMODE) {
		if (m_isMouseDown) {
			CPen pen(PS_DOT, 1, RGB(0, 0, 0));
			memDC.SelectObject(pen);
			memDC.SelectStockObject(NULL_BRUSH);
			memDC.Rectangle(m_clickPos1.x, m_clickPos1.y, m_clickPos2.x, m_clickPos2.y);
		}
		POSITION pos = m_selectedShapes.m_group.GetHeadPosition();
		while (pos != NULL) {
			CMyShape* pShape = m_selectedShapes.m_group.GetNext(pos);
			pShape->setBorder(memDC);
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
		m_pShapes.AddTail(shape);
	}
	else if (m_curMode == CIRCLEMODE) {	//원
		CMyShape* shape = new CMyCircle();
		shape->doMouseDown(point);
		m_pShapes.AddTail(shape);
	}
	else if (m_curMode == CURVEMODE) {	//곡선
		CMyShape* shape = new CMyCurve();
		shape->doMouseDown(point);
		m_pShapes.AddTail(shape);
	}
	else if (m_curMode == STARMODE) {	//별
		CMyShape* shape = new CMyStar();
		shape->doMouseDown(point);
		m_pShapes.AddTail(shape);
	}
	else if (m_curMode == SELECTMODE) {	//선택모드
		
		m_clickPos1 = CPoint(point);
		m_clickPos2 = CPoint(point);
		POSITION pos = m_pShapes.GetHeadPosition();
		while (pos != NULL) {
			CMyShape*& shape = m_pShapes.GetNext(pos);
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
	if (m_curMode != SELECTMODE) {
		m_pShapes.GetTail()->doMouseUp(point);
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

		POSITION pos = m_pShapes.GetHeadPosition();
		while (pos != NULL) {
			CMyShape*& p = m_pShapes.GetNext(pos);
			if (p->m_lt.x > left && p->m_lt.y > top && p->m_rb.x < right && p->m_rb.y < bottom) {

				m_selectedShapes.addShape(p);
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
		TRACE("p1=(%d, %d), p2=(%d,%d)\n", m_clickPos1.x, m_clickPos1.y, m_clickPos2.x, m_clickPos2.y);
		if (m_curMode != SELECTMODE) {
			m_pShapes.GetTail()->doMouseUp(point);
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


void CChildView::OnUpdateRectangle(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_curMode == RECTANGLEMODE) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
	
}


void CChildView::OnUpdateSelect(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_curMode == SELECTMODE) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CChildView::OnUpdateCurve(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_curMode == CURVEMODE) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CChildView::OnUpdateCircle(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_curMode == CIRCLEMODE) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CChildView::OnUpdateGroup(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if(m_selectedShapes.m_group.GetSize()>1) pCmdUI->Enable(true);
	else pCmdUI->Enable(false);
}


void CChildView::OnUpdateUngroup(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_selectedShapes.m_group.GetSize() > 0) pCmdUI->Enable(true);
	else pCmdUI->Enable(false);
}

void CChildView::OnBringfront()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	POSITION selectedPos = m_selectedShapes.m_group.GetHeadPosition();

	while (selectedPos != NULL) {

		POSITION prevSelected = selectedPos;
		CMyShape* selected = m_selectedShapes.m_group.GetNext(selectedPos);
		POSITION pShapePos = m_pShapes.GetHeadPosition();

		while (pShapePos != NULL) {

			POSITION pShapeprev = pShapePos;

			CMyShape* pShape = m_pShapes.GetNext(pShapePos);

			if (pShape == selected) {
				CMyShape* shape = m_pShapes.GetAt(pShapeprev);
				m_pShapes.RemoveAt(pShapeprev);
				m_pShapes.AddTail(shape);
			}
		}
	}
	Invalidate();


}


void CChildView::OnUpdateBringback(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if(m_selectedShapes.m_group.GetSize() > 0) pCmdUI->Enable(true);
	else pCmdUI->Enable(false);
}


void CChildView::OnUpdateBringfront(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_selectedShapes.m_group.GetSize() > 0) pCmdUI->Enable(true);
	else pCmdUI->Enable(false);
}


void CChildView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CMenu menu;
	menu.LoadMenuW(IDR_MAINFRAME);

	CMenu *pMenu = menu.GetSubMenu(4);
	pMenu->TrackPopupMenu(
		TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		point.x, point.y, AfxGetMainWnd());

}


void CChildView::OnBringback()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	POSITION selectedPos = m_selectedShapes.m_group.GetHeadPosition();

	while (selectedPos != NULL) {

		POSITION prevSelected = selectedPos;
		CMyShape* selected = m_selectedShapes.m_group.GetNext(selectedPos);
		POSITION pShapePos = m_pShapes.GetHeadPosition();

		while (pShapePos != NULL) {

			POSITION pShapeprev = pShapePos;

			CMyShape* pShape = m_pShapes.GetNext(pShapePos);

			if (pShape == selected) {
				CMyShape* shape = m_pShapes.GetAt(pShapeprev);
				m_pShapes.RemoveAt(pShapeprev);
				m_pShapes.AddHead(shape);
			}
		}
	}
	Invalidate();

}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nChar == VK_DELETE) {

		POSITION selectedPos = m_selectedShapes.m_group.GetHeadPosition();

		while (selectedPos != NULL) {

			POSITION prevSelected = selectedPos;
			CMyShape* selected = m_selectedShapes.m_group.GetNext(selectedPos);
			POSITION pShapePos = m_pShapes.GetHeadPosition();

			while (pShapePos != NULL) {
				
				POSITION pShapeprev = pShapePos;

				CMyShape* pShape = m_pShapes.GetNext(pShapePos);

				if (pShape == selected) {
					m_pShapes.RemoveAt(pShapeprev);
					m_selectedShapes.m_group.RemoveAt(prevSelected);
				}
			}
		}
		Invalidate();
	}

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
