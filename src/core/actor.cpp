#include "actor.h"
using namespace Core;

void Actor::init()
{
    this->addComponent<TransformComponent>(_transform);
    // _transform.reset();
    // _transform = this->getComponent<TransformComponent>();
}

int Actor::getID()
{
    return m_id;
}