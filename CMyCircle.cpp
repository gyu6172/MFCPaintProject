#include "pch.h"
#include "CMyCircle.h"

CMyCircle::CMyCircle()
{
	m_radius = 0;
	m_midpoint = CPoint(0,0);
}

void CMyCircle::draw(CDC& dc)
{
	CPen pen(PS_SOLID, 3, m_borderColor);
	CBrush brush(m_shapeColor);
	dc.SelectObject(pen);
	dc.SelectObject(brush);
	dc.Ellipse(m_midpoint.x-m_radius, m_midpoint.y-m_radius, m_midpoint.x+m_radius, m_midpoint.y+m_radius);

}

bool CMyCircle::isClicked(CPoint p)
{
	int distance = sqrt((m_midpoint.x-p.x)*(m_midpoint.x-p.x) + (m_midpoint.y-p.y)*(m_midpoint.y-p.y));
	if(distance <= m_radius) return true;
	else return false;
}

void CMyCircle::doMouseUp(CPoint p)
{
	int distance = sqrt((m_midpoint.x - p.x) * (m_midpoint.x - p.x) + (m_midpoint.y - p.y) * (m_midpoint.y-p.y));
	m_radius = distance;

	m_lt.x = m_midpoint.x-m_radius-5;
	m_lt.y = m_midpoint.y-m_radius-5;
	m_rb.x = m_midpoint.x+m_radius+5;
	m_rb.y = m_midpoint.y+m_radius+5;

}

void CMyCircle::doMouseDown(CPoint p)
{
	m_midpoint = p;
	m_radius = 0;

	m_lt.x = m_midpoint.x - 5;
	m_lt.y = m_midpoint.y - 5;
	m_rb.x = m_midpoint.x + 5;
	m_rb.y = m_midpoint.y + 5;
}

void CMyCircle::move(int dx, int dy)
{
	m_midpoint.x += dx;
	m_midpoint.y += dy;

	m_lt.x += dx; 
	m_lt.y += dy;
	m_rb.x += dx;
	m_rb.y += dy;
}
