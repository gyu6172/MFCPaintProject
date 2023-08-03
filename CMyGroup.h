#pragma once
#include <vector>
#include "CMyShape.h"
#include <algorithm>
class CMyGroup : public CMyShape
{

private:
	void updateLTRB();

public:
	CList<CMyShape*> m_group;

	CMyGroup();
	CMyGroup(CMyShape* shape);
	CMyGroup(CList<CMyShape*>& shapes);
	bool isClicked(CPoint p);
	void setBorder(CDC& dc);
	void draw(CDC& dc);
	void move(int dx, int dy);
	void doMouseUp(CPoint p);
	void doMouseDown(CPoint p);
	void addShape(CMyShape* p);
	POSITION getHeadPosition();
	void clear();
};

