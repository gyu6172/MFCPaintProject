#pragma once
#include "CMyShape.h"
#include <vector>
class CMyCurve :
    public CMyShape
{
private:
    int m_radius;
 public:
    CList<CPoint> m_pts;

    CMyCurve();

    void draw(CDC& dc);
    bool isClicked(CPoint p);
    void doMouseUp(CPoint p);
    void doMouseDown(CPoint p);
    void move(int dx, int dy);
};

