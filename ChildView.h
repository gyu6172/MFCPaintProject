
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once


// CChildView 창
#include "CMyShape.h"
#include "CMyGroup.h"
class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:
	CList<CMyShape*> m_pShapes;
	int m_curMode;
	CPoint m_clickPos1;
	CPoint m_clickPos2;
	bool m_isSelected;
	bool m_isMouseDown;
	CMyGroup m_selectedShapes;

// 작업입니다.
public:

// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRectangle();
	afx_msg void OnCircle();
	afx_msg void OnCurve();
	afx_msg void OnStar();
	afx_msg void OnSelect();
	afx_msg void OnGroup();
	afx_msg void OnUngroup();
	afx_msg void OnUpdateRectangle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSelect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCurve(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCircle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGroup(CCmdUI* pCmdUI);
	afx_msg void OnUpdateUngroup(CCmdUI* pCmdUI);
//	afx_msg void OnBringback();
	afx_msg void OnBringfront();
	afx_msg void OnUpdateBringback(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBringfront(CCmdUI* pCmdUI);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnBringback();
};

