#include "pch.h"
#include "CMyRectangle.h"
#include <algorithm>

CMyRectangle::CMyRectangle()
{
	m_P = CPoint(0,0);
	m_Q = CPoint(0,0);
	m_left = 0;
	m_top = 0;
	m_right = 0;
	m_bottom = 0;
}

void CMyRectangle::draw(CDC& dc)
{
	CPen pen(PS_SOLID, 3, m_borderColor);
	CBrush brush(m_shapeColor);
	dc.SelectObject(pen);
	dc.SelectObject(brush);
	dc.Rectangle(m_P.x, m_P.y, m_Q.x, m_Q.y);

}

bool CMyRectangle::isClicked(CPoint p)
{
	if (m_left <= p.x && p.x <= m_right && m_top <= p.y && p.y <= m_bottom) {
		return true;
	}
	else {
		return false;
	}
}

void CMyRectangle::doMouseUp(CPoint p)
{
	m_Q = p;

	m_left = min(m_P.x, m_Q.x);
	m_top = min(m_P.y, m_Q.y);
	m_right = max(m_P.x, m_Q.x);
	m_bottom = max(m_P.y, m_Q.y);

	m_lt.x = m_left - 5;
	m_lt.y = m_top - 5;
	m_rb.x = m_right + 5;
	m_rb.y = m_bottom + 5;

	TRACE("lt:(%d, %d), rb:(%d, %d)\n",m_left, m_top, m_right, m_bottom);
}

void CMyRectangle::doMouseDown(CPoint p)
{
	m_P = p;
	m_Q = p;

	m_left = p.x;
	m_right = p.x;
	m_top = p.y;
	m_bottom = p.y;

	m_lt.x = m_left - 5;
	m_lt.y = m_top - 5;
	m_rb.x = m_right + 5;
	m_rb.y = m_bottom + 5;
}

void CMyRectangle::move(int dx, int dy)
{
	m_P.x += dx;
	m_P.y += dy;
	m_Q.x += dx;
	m_Q.y += dy;

	m_left += dx;
	m_right += dx;
	m_top += dy;
	m_bottom += dy;

	m_lt.x += dx;
	m_lt.y += dy;
	m_rb.x += dx;
	m_rb.y += dy;
}
