#pragma once
#include "CMyShape.h"
class CMyRectangle :
    public CMyShape
{
public:
    int m_left;
    int m_right;
    int m_top;
    int m_bottom;

    CMyRectangle();
    CMyRectangle(CPoint p1, CPoint p2);
    CMyRectangle(int x1, int y1, int x2, int y2);

    void draw(CDC& dc);
    bool isClicked(int x, int y);
};

