#include "pch.h"
#include "CMyCircle.h"

CMyCircle::CMyCircle()
{
	m_radius = 0;
	m_midpoint = CPoint(0,0);
}

CMyCircle::CMyCircle(CPoint mid, int r)
{
	m_midpoint = mid;
	m_radius = r;

	m_lt.x = m_midpoint.x-r-5;
	m_lt.y = m_midpoint.y-r-5;
	m_rb.x = m_midpoint.x+r+5;
	m_rb.y = m_midpoint.y+r+5;
}

CMyCircle::CMyCircle(int x, int y, int r)
{
	m_midpoint = CPoint(x,y);
	m_radius = r;

	m_lt.x = m_midpoint.x - r - 5;
	m_lt.y = m_midpoint.y - r - 5;
	m_rb.x = m_midpoint.x + r + 5;
	m_rb.y = m_midpoint.y + r + 5;
}

void CMyCircle::draw(CDC& dc)
{
	CPen pen(PS_SOLID, 3, m_borderColor);
	dc.SelectObject(pen);
	dc.Ellipse(m_midpoint.x-m_radius, m_midpoint.y-m_radius, m_midpoint.x+m_radius, m_midpoint.y+m_radius);

	CBrush brush(m_shapeColor);
	dc.SelectObject(brush);
	dc.Ellipse(m_midpoint.x - m_radius, m_midpoint.y - m_radius, m_midpoint.x + m_radius, m_midpoint.y + m_radius);

}

bool CMyCircle::isClicked(int x, int y)
{
	int distance = sqrt((m_midpoint.x-x)*(m_midpoint.x-x) + (m_midpoint.y-y)*(m_midpoint.y));
	if(distance <= m_radius) return true;
	else return false;
}
