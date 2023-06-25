#include "pch.h"
#include "CMyCurve.h"

CMyCurve::CMyCurve()
{
    m_radius = 3;
}

void CMyCurve::draw(CDC& dc)
{
    CPen pen(PS_SOLID, m_radius, m_shapeColor);
    dc.SelectObject(pen);
    POSITION pos = m_pts.GetHeadPosition();
    while (pos != NULL) {
        dc.MoveTo(m_pts.GetNext(pos));
        if(pos==NULL) break;
        dc.LineTo(m_pts.GetAt(pos));
    }
}

bool CMyCurve::isClicked(CPoint p)
{
    float min_dist = FLT_MAX;
    POSITION pos = m_pts.GetHeadPosition();
    while (pos != NULL) {
        float dist = sqrt((m_pts.GetAt(pos).x - p.x) * (m_pts.GetAt(pos).x - p.x) + (m_pts.GetAt(pos).y - p.y) * (m_pts.GetNext(pos).y - p.y));
        if (dist < min_dist) {
            min_dist = dist;
        }
    }
    if(min_dist < m_radius+10) return true;
    else return false;
}

void CMyCurve::doMouseUp(CPoint p)
{
    m_pts.AddTail(p);

    m_lt.x = min(m_lt.x, p.x);
    m_lt.y = min(m_lt.y, p.y);
    m_rb.x = max(m_rb.x, p.x);
    m_rb.y = max(m_rb.y, p.y);
}

void CMyCurve::doMouseDown(CPoint p)
{
    
    m_pts.AddTail(p);

    m_lt.x = p.x-5;
    m_lt.y = p.y-5;
    m_rb.x = p.x+5;
    m_rb.y = p.y+5;

}

void CMyCurve::move(int dx, int dy)
{
    POSITION pos = m_pts.GetHeadPosition();
    while (pos != NULL) {
        m_pts.GetAt(pos).x += dx;
        m_pts.GetNext(pos).y += dy;
    }
     
    m_lt.x += dx;
    m_lt.y += dy;
    m_rb.x += dx;
    m_rb.y += dy;
}
