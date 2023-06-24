#pragma once
#include "CMyShape.h"
class CMyCircle :
    public CMyShape
{
public:
    int m_radius;
    CPoint m_midpoint;

    CMyCircle();

    void draw(CDC &dc);
    bool isClicked(CPoint p);
    void doMouseUp(CPoint p);
    void doMouseDown(CPoint p);
    void move(int dx, int dy);
};

