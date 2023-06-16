#include "pch.h"
#include "CMyShape.h"

CMyShape::CMyShape()
{
	m_lt = CPoint(0,0);
	m_rb = CPoint(0,0);
	m_shapeColor = RGB(rand()%256, rand() % 256, rand() % 256);
	m_borderColor = RGB(rand()%256, rand() % 256, rand() % 256);
}
