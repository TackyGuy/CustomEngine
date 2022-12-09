#include "collidercomponent.h"
using namespace Core;

const size_t ColliderComponent::Type = std::hash<std::string>{}("Collider");

BoundingBox *ColliderComponent::getAABB()
{
    return m_aabb;
}

bool ColliderComponent::isDirty() const
{
    return m_dirtyFlag;
}
void ColliderComponent::setDirty(bool val)
{
    m_dirtyFlag = val;
}

const std::string& ColliderComponent::getTag() const
{
    return m_tag;
}