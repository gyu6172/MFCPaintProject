#pragma once
#include "CMyShape.h"
#include <vector>
class CMyCurve :
    public CMyShape
{
private:
    int m_radius;
 public:
    std::vector<CPoint> m_pts;

    CMyCurve();

    void draw(CDC& dc);
    bool isClicked(int x, int y);
    void doMouseUp(CPoint p);
    void doMouseDown(CPoint p);
};

