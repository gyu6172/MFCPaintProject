#pragma once
class CMyShape
{
protected:
	CPoint m_lt, m_rb;
	COLORREF m_shapeColor, m_borderColor;

public:
	CMyShape();
	virtual void draw(CDC &dc) = 0;
	virtual bool isClicked(int x, int y) = 0;
};

