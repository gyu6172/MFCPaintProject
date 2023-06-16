#pragma once
#include "CMyShape.h"
#include <vector>
class CMyStar :
    public CMyShape
{
private:
    CPoint m_midpoint;
    int m_radius;
    float m_theta;
    CPoint m_outpts[5];
    CPoint m_inpts[5];

public:
    std::vector<CPoint> m_pts;

    CMyStar();

    void draw(CDC& dc);
    bool isClicked(int x, int y);
    void doMouseUp(CPoint p);
    void doMouseDown(CPoint p);
};

