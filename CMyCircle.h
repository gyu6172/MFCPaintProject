#pragma once
#include "CMyShape.h"
class CMyCircle :
    public CMyShape
{
public:
    int m_radius;
    CPoint m_midpoint;

    CMyCircle();
    CMyCircle(CPoint mid, int r);
    CMyCircle(int x, int y, int r);

    void draw(CDC &dc);
    bool isClicked(int x, int y);
};

