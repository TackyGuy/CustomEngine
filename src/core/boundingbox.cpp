#include "boundingbox.h"
using namespace Core;

void BoundingBox::setCenter(const Vector2& center)
{
    m_center = center;
    m_min = m_center - m_extents;
    m_max = m_center + m_extents;
}
const Vector2& BoundingBox::getCenter() const
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
void BoundingBox::setExtents(Vector2 vec2)
{
    m_extents = vec2;
}
const Vector2& BoundingBox::getExtents() const
{
    return m_extents;
}
const Vector2& BoundingBox::getSize() const
{
    return m_size;
}
const Vector2& BoundingBox::getMin() const
{
    return m_min;
}
const Vector2& BoundingBox::getMax() const
{
    return m_max;
}