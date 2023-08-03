#include "pch.h"
#include "CMyGroup.h"

void CMyGroup::updateLTRB()
{
    int minX = INT_MAX, minY = INT_MAX, maxX = -1, maxY = -1;

    POSITION pos = m_group.GetHeadPosition();
    while (pos != NULL) {
        CMyShape*& pShape = m_group.GetNext(pos);

        minX = min(minX, pShape->m_lt.x);
        minY = min(minY, pShape->m_lt.y);
        maxX = max(maxX, pShape->m_rb.x);
        maxY = max(maxY, pShape->m_rb.y);
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
    m_group.AddTail(shape);
    updateLTRB();

}

CMyGroup::CMyGroup(CList<CMyShape*>& shapes)
{
    POSITION pos = shapes.GetHeadPosition();
    while (pos != NULL) {
        CMyShape* pShape = m_group.GetNext(pos);
        m_group.AddTail(pShape);
    }
    updateLTRB();
}

bool CMyGroup::isClicked(CPoint p)
{
    POSITION pos = m_group.GetHeadPosition();
    while (pos != NULL) {
        CMyShape*& pShape = m_group.GetNext(pos);
        if (pShape->isClicked(p)) {
            return true;
        }
        
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
    POSITION pos = m_group.GetHeadPosition();
    while (pos != NULL) {
        CMyShape*& pShape = m_group.GetNext(pos);
        pShape->draw(dc);
    }
}

void CMyGroup::move(int dx, int dy)
{
    POSITION pos = m_group.GetHeadPosition();
    while (pos != NULL) {
        CMyShape*& pShape = m_group.GetNext(pos);
        pShape->move(dx, dy);
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
    POSITION pos = m_group.GetHeadPosition();
    while (pos != NULL) {
        if (m_group.GetNext(pos) == p) {
            return;
        }
    }
    m_group.AddTail(p);
    updateLTRB();
}

POSITION CMyGroup::getHeadPosition()
{
    POSITION pos = m_group.GetHeadPosition();
    return pos;
}

void CMyGroup::clear()
{
    m_group.RemoveAll();
}
