#include "pch.h"
#include "CMyStar.h"

CMyStar::CMyStar()
{
	m_midpoint = CPoint(0,0);
    m_radius = 0;
	m_theta = -2.0f * (3.1415926535897932) / 5;
}

void CMyStar::draw(CDC& dc)
{
	CPen pen(PS_SOLID, 3, m_borderColor);
	CBrush brush(m_shapeColor);
	dc.SelectObject(pen);
	dc.SelectObject(brush);
	dc.Polygon(m_pts, 10);

}

bool CMyStar::isClicked(int x, int y)
{
    return false;
}

void CMyStar::doMouseUp(CPoint p)
{

    m_radius = sqrt((p.x-m_midpoint.x)*(p.x - m_midpoint.x) + (p.y - m_midpoint.y)*(p.y - m_midpoint.y));
	m_outpts[0] = CPoint(m_midpoint.x, m_midpoint.y - m_radius);
	m_inpts[0] = CPoint(m_midpoint.x, m_midpoint.y + m_radius/2.8f);

	for (int i = 1; i < 5; i++) {	

		CPoint outP = m_outpts[i - 1];
		int x1 = cos(m_theta) * (outP.x - m_midpoint.x) - sin(m_theta) * (outP.y - m_midpoint.y) + m_midpoint.x;
		int y1 = sin(m_theta) * (outP.x - m_midpoint.x) + cos(m_theta) * (outP.y - m_midpoint.y) + m_midpoint.y;

		CPoint inP = m_inpts[i - 1];
		int x2 = cos(m_theta) * (inP.x - m_midpoint.x) - sin(m_theta) * (inP.y - m_midpoint.y) + m_midpoint.x;
		int y2 = sin(m_theta) * (inP.x - m_midpoint.x) + cos(m_theta) * (inP.y - m_midpoint.y) + m_midpoint.y;

		m_outpts[i] = CPoint(x1, y1);
		m_inpts[i] = CPoint(x2, y2);
	}

	for (int i = 0; i < 5; i++) {
		m_pts[2*i] = m_outpts[i];
		m_pts[2*i+1] = m_inpts[(i+3)%5];
	}

}

void CMyStar::doMouseDown(CPoint p)
{
	m_midpoint = p;
	m_radius = 0;

	m_lt = CPoint(0,0);
	m_rb = CPoint(0,0);
}
