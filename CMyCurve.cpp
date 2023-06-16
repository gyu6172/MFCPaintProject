#include "pch.h"
#include "CMyCurve.h"

CMyCurve::CMyCurve()
{
    m_radius = 10;
}

void CMyCurve::draw(CDC& dc)
{
    CPen pen(PS_SOLID, m_radius, m_shapeColor);
    for (int i = 0; i < m_pts.size()-1; i++) {
        dc.MoveTo(m_pts[i]);
        dc.LineTo(m_pts[i+1]);
    }
}

bool CMyCurve::isClicked(int x, int y)
{
    float min_dist = FLT_MAX;
    for (auto pt : m_pts) {
        float dist = sqrt((pt.x-x)*(pt.x-x) + (pt.y-y)*(pt.y-y));
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

}

void CMyCurve::doMouseDown(CPoint p)
{
    
    m_pts.push_back(p);
}
