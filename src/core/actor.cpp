#include "actor.h"
using namespace Core;

void Actor::init()
{
    this->addComponent<TransformComponent>(TransformComponent(this, _transform->getPosition(), _transform->getScale()));
    _transform = this->getComponent<TransformComponent>();
}

int Actor::getID()
{
    return m_id;
}

void Actor::setParent(Actor* parent)
{
    _parent = parent;
}

Actor* Actor::getParent()
{
    return _parent;
}