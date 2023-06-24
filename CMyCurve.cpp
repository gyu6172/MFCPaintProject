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
    for (int i = 0; i < m_pts.size()-1; i++) {
        dc.MoveTo(m_pts[i]);
        dc.LineTo(m_pts[i+1]);
    }
}

bool CMyCurve::isClicked(CPoint p)
{
    float min_dist = FLT_MAX;
    for (auto pt : m_pts) {
        float dist = sqrt((pt.x-p.x)*(pt.x-p.x) + (pt.y-p.y)*(pt.y-p.y));
        if (dist < min_dist) {
            min_dist = dist;
        }
    }
    if(min_dist < m_radius+10) return true;
    else return false;
}

void CMyCurve::doMouseUp(CPoint p)
{
    m_pts.push_back(p);

    int minx = INT_MAX, miny = INT_MAX;
    int maxx = -1, maxy = -1;
    for (auto p : m_pts) {
        minx = min(minx, p.x);
        miny = min(miny, p.y);
        maxx = max(maxx, p.x);
        maxy = max(maxy, p.y);
    }
    m_lt.x = minx;
    m_lt.y = miny;
    m_rb.x = maxx;
    m_rb.y = maxy;
}

void CMyCurve::doMouseDown(CPoint p)
{
    
    m_pts.push_back(p);
}

void CMyCurve::move(int dx, int dy)
{
    for (auto p : m_pts) {
        p.x += dx;
        p.y += dy;
    }
     
    m_lt.x += dx;
    m_lt.y += dy;
    m_rb.x += dx;
    m_rb.y += dy;
}
