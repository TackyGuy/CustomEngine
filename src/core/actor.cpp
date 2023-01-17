#include "actor.h"
using namespace Core;

const bool Actor::isReady() const
{
    return m_ready;
}

void Actor::setActive(bool value)
{
    m_active = value;
    if (_components.size() > 0)
    {
        for (auto pair : _components)
        {
            auto component = pair.second;
            component->setActive(value);
        }
    }
    if (_children.size() > 0)
    {
        for (auto child : _children)
        {
            if (child) child->setActive(value);
        }
    }
}
const bool Actor::isActive() const
{
    return m_active;
}

const int Actor::getID() const
{
    return m_id;
}

void Actor::setParent(std::shared_ptr<Actor> parent)
{
    _parent = parent;
}
std::shared_ptr<Actor> Actor::getParent()
{
    return _parent;
}
void Actor::attachChild(std::shared_ptr<Actor> child)
{
    _children.emplace_back(child);
    if (_transform) _transform->attachChild(child->getComponent<TransformComponent>());
}
std::shared_ptr<Actor> Actor::getChild(uint32_t index)
{
    if (index < _children.size()) return _children.at(index);

    return nullptr;
}
std::vector<std::shared_ptr<Actor>> Actor::getChildren()
{
    return _children;
}
const int Actor::getChildrenCount() const
{
    return _children.size();
}
