#include "pch.h"
#include "CMyRectangle.h"

CMyRectangle::CMyRectangle()
{
	m_left = 0;
	m_top = 0;
	m_right = 0;
	m_bottom = 0;
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

void CMyRectangle::doMouseUp(CPoint p)
{
	if (p.x > m_left)
		m_right = p.x;
	else
		m_left = p.x;

	if (p.y > m_top)
		m_bottom = p.y;
	else
		m_top = p.y;

	m_lt.x = m_left - 5;
	m_lt.y = m_top - 5;
	m_rb.x = m_right + 5;
	m_rb.y = m_bottom + 5;
}

void CMyRectangle::doMouseDown(CPoint p)
{
	m_left = p.x;
	m_right = p.x;
	m_top = p.y;
	m_bottom = p.y;

	m_lt.x = m_left - 5;
	m_lt.y = m_top - 5;
	m_rb.x = m_right + 5;
	m_rb.y = m_bottom + 5;
}
