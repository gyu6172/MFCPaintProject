#pragma once
class CMyShape
{
protected:
	CPoint m_lt, m_rb;
	COLORREF m_shapeColor, m_borderColor;

public:
	CMyShape();
	virtual void draw(CDC &dc) = 0;
	virtual bool isClicked(CPoint p) = 0;
	virtual void doMouseUp(CPoint p) = 0;
	virtual void doMouseDown(CPoint p) = 0;
	virtual void move(int dx, int dy) = 0;
	void setBorder(CDC &dc);
};

