#include "pch.h"
#include "CMyRectangle.h"

CMyRectangle::CMyRectangle()
{
	m_left = 0;
	m_top = 0;
	m_right = 0;
	m_bottom = 0;
}

CMyRectangle::CMyRectangle(CPoint p1, CPoint p2)
{
	m_left = min(p1.x, p2.x);
	m_top = min(p1.y, p2.y);
	m_right = max(p1.x, p2.x);
	m_bottom = max(p1.y, p2.y);

	m_lt.x = m_left - 5;
	m_lt.y = m_top - 5;
	m_rb.x = m_right + 5;
	m_rb.y = m_bottom + 5;
}

CMyRectangle::CMyRectangle(int x1, int y1, int x2, int y2)
{
	m_left = min(x1, x2);
	m_top = min(y1, y2);
	m_right = max(x1, x2);
	m_bottom = max(y1, y2);

	m_lt.x = m_left-5;
	m_lt.y = m_top-5;
	m_rb.x = m_right+5;
	m_rb.y = m_bottom+5;
	//만약 나간다면?
}

void CMyRectangle::draw(CDC& dc)
{
	CPen pen(PS_SOLID, 3, m_borderColor);
	dc.SelectObject(pen);
	dc.Rectangle(m_left, m_top, m_right, m_bottom);

	CBrush brush(m_shapeColor);
	dc.SelectObject(brush);
	dc.Rectangle(m_left, m_top, m_right, m_bottom);
}

bool CMyRectangle::isClicked(int x, int y)
{
	if (m_left <= x && x <= m_right && m_top <= y && y <= m_bottom) {
		return true;
	}
	else {
		return false;
	}
}
