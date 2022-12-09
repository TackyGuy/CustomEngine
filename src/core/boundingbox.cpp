#include "boundingbox.h"
using namespace Core;

void BoundingBox::setCenter(const Vector2& center)
{
    m_center = center;
    m_min = m_center - m_extents;
    m_max = m_center + m_extents;
}
Vector2& BoundingBox::getCenter()
{
    return m_center;
}
void BoundingBox::expand(float val)
{
    m_extents.add(val, val);
}
void BoundingBox::expand(float x, float y)
{
    m_extents.add(x, y);
}
void BoundingBox::expand(Vector2 vec2)
{
    m_extents.add(vec2);
}
Vector2& BoundingBox::getExtents()
{
    return m_extents;
}
Vector2& BoundingBox::getSize()
{
    return m_size;
}
Vector2& BoundingBox::getMin()
{
    return m_min;
}
Vector2& BoundingBox::getMax()
{
    return m_max;
}