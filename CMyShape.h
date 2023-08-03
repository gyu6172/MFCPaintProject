#pragma once
class CMyShape
{
protected:
	COLORREF m_shapeColor, m_borderColor;
public:
	CList<CMyShape*> m_group;
	CPoint m_lt, m_rb;
	CMyShape();
	virtual void draw(CDC &dc) = 0;
	virtual bool isClicked(CPoint p) = 0;
	virtual void doMouseUp(CPoint p) = 0;
	virtual void doMouseDown(CPoint p) = 0;
	virtual void move(int dx, int dy) = 0;
	virtual POSITION getHeadPosition();
	void setBorder(CDC &dc);
};

