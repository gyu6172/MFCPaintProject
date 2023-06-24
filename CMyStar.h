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
    CPoint m_pts[10];

    CMyStar();

    void draw(CDC& dc);
    bool isClicked(CPoint p);
    void doMouseUp(CPoint p);
    void doMouseDown(CPoint p);
    void move(int dx, int dy);
};

