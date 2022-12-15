#include "rigidbodycomponent.h"
using namespace Core;

const size_t RigidbodyComponent::Type = std::hash<std::string>{}("Rigidbody");

void RigidbodyComponent::resolveCollision()
{
    Vector2 previousPosition = _transform->getPosition();
    Vector2 currentPosition = previousPosition + m_velocity;
    _collider->getAABB().setCenter(currentPosition);

    auto other = Collision::getClosestCollider(_collider);
    Vector2 direction = m_velocity;
    direction.normalize();

    while (other != nullptr)
    {
        // std::cout << "Closest collider to " << _collider->getTag() << " is " << other->getTag() << std::endl;
        currentPosition.substract(direction);
        _collider->getAABB().setCenter(currentPosition);

        other = Collision::getClosestCollider(_collider);
    }

    _transform->setPosition(currentPosition);
    _collider->setDirty(true);
}

void RigidbodyComponent::setVelocity(Vector2& vec2)
{
    m_velocity = vec2;
}

const Vector2& RigidbodyComponent::getVelocity() const
{
    return m_velocity;
}

std::shared_ptr<ColliderComponent> RigidbodyComponent::getCollider()
{
    return _collider;
}