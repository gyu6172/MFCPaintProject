#pragma once
#include "CMyShape.h"
class CMyRectangle :
    public CMyShape
{
private:
    CPoint m_P, m_Q;

public:
    int m_left;
    int m_right;
    int m_top;
    int m_bottom;


    CMyRectangle();

    void draw(CDC& dc);
    bool isClicked(int x, int y);
    void doMouseUp(CPoint p);
    void doMouseDown(CPoint p);
};

