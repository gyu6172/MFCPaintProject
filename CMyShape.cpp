#include "pch.h"
#include "CMyShape.h"

CMyShape::CMyShape()
{
	m_lt = CPoint(0,0);
	m_rb = CPoint(0,0);
	m_shapeColor = RGB(rand()%256, rand() % 256, rand() % 256);
	m_borderColor = RGB(rand()%256, rand() % 256, rand() % 256);
}

POSITION CMyShape::getHeadPosition()
{
	return NULL;
}

void CMyShape::setBorder(CDC &dc)
{
	CPen pen(PS_DOT, 1, RGB(255,0,0));
	dc.SelectObject(pen);
	dc.SelectStockObject(NULL_BRUSH);
	dc.Rectangle(m_lt.x, m_lt.y, m_rb.x, m_rb.y);
}
