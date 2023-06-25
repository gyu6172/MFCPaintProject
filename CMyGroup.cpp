#include "pch.h"
#include "CMyGroup.h"

void CMyGroup::updateLTRB()
{
    int minX = INT_MAX, minY = INT_MAX, maxX = -1, maxY = -1;
    for (auto shape : m_group) {
        minX = min(minX, shape->m_lt.x);
        minY = min(minY, shape->m_lt.y);
        maxX = max(maxX, shape->m_rb.x);
        maxY = max(maxY, shape->m_rb.y);
    }
    m_lt = CPoint(minX, minY);
    m_rb = CPoint(maxX, maxY); 
}

CMyGroup::CMyGroup()
{
    m_lt = CPoint(0, 0);
    m_rb = CPoint(0, 0);
}

CMyGroup::CMyGroup(CMyShape* shape)
{
    m_group.push_back(shape);
    updateLTRB();
}

CMyGroup::CMyGroup(std::vector<CMyShape*> shapes)
{
    for (auto p : shapes) {
        m_group.push_back(p);
    }
    updateLTRB();
}

bool CMyGroup::isClicked(CPoint p)
{
    for (auto shape : m_group) {
        if(shape->isClicked(p)) return true;
    }
    return false;
}

void CMyGroup::setBorder(CDC& dc)
{
    
    CPen pen(PS_DOT, 1, RGB(255,0,0));
    dc.SelectObject(pen);
    dc.Rectangle(m_lt.x, m_lt.y, m_rb.x, m_rb.y);
}

void CMyGroup::draw(CDC& dc)
{
    for (auto shape : m_group) {
        shape->draw(dc);
    }
}

void CMyGroup::move(int dx, int dy)
{
    for (auto shape : m_group) {
        shape->move(dx, dy);
    }
    updateLTRB();
}

void CMyGroup::doMouseUp(CPoint p)
{
}

void CMyGroup::doMouseDown(CPoint p)
{
}

void CMyGroup::addShape(CMyShape* p)
{
    m_group.push_back(p);
    updateLTRB();
}

void CMyGroup::clear()
{
    m_group.clear();
}
