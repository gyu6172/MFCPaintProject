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
	dc.SelectObject(pen);
	for (int i = 0; i < m_pts.size()-1; i++) {
		dc.MoveTo(m_pts[i]);
		dc.LineTo(m_pts[i+1]);
	}
	dc.MoveTo(m_pts[m_pts.size()-1]);
	dc.LineTo(m_pts[0]);
	
}

bool CMyStar::isClicked(int x, int y)
{
    return false;
}

void CMyStar::doMouseUp(CPoint p)
{
    m_radius = sqrt((p.x-m_midpoint.x)*(p.x - m_midpoint.x) + (p.y - m_midpoint.y)*(p.y - m_midpoint.y));
	//m_outpts[0] = CPoint(p.x, p.y - m_radius);
	//m_inpts[0] = CPoint(p.x, p.y + m_radius);

	//for (int i = 1; i < 5; i++) {
	//	CPoint prevP1 = m_outpts[i - 1];
	//	int x1 = cos(m_theta) * (prevP1.x - m_midpoint.x) - sin(m_theta) * (prevP1.y - m_midpoint.y) + m_midpoint.x;
	//	int y1 = sin(m_theta) * (prevP1.x - m_midpoint.x) + cos(m_theta) * (prevP1.y - m_midpoint.y) + m_midpoint.y;

	//	CPoint prevP2 = m_inpts[i - 1];
	//	int x2 = cos(m_theta) * (prevP2.x - m_midpoint.x) - sin(m_theta) * (prevP2.y - m_midpoint.y) + m_midpoint.x;
	//	int y2 = sin(m_theta) * (prevP2.x - m_midpoint.x) + cos(m_theta) * (prevP2.y - m_midpoint.y) + m_midpoint.y;
	//	m_outpts[i] = CPoint(x1, y1);
	//	m_inpts[i] = CPoint(x2, y2);
	//}

	//for (int i = 0; i < 5; i++) {
	//	m_pts.push_back(m_outpts[i]);
	//	m_pts.push_back(m_inpts[(i+3)%5]);
	//}

	m_pts.push_back(CPoint(p.x, p.y - m_radius));
	for (int i = 1; i < 5; i++) {
		CPoint prevP1 = m_pts[i - 1];
		int x1 = cos(m_theta) * (prevP1.x - m_midpoint.x) - sin(m_theta) * (prevP1.y - m_midpoint.y) + m_midpoint.x;
		int y1 = sin(m_theta) * (prevP1.x - m_midpoint.x) + cos(m_theta) * (prevP1.y - m_midpoint.y) + m_midpoint.y;
		m_pts.push_back(CPoint(x1, y1));
	}

}

void CMyStar::doMouseDown(CPoint p)
{
	m_midpoint = p;
	m_radius = 0;
}
