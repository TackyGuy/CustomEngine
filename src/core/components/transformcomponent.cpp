#include "transformcomponent.h"
using namespace Core;

const size_t TransformComponent::Type = std::hash<std::string>{}("TRANSFORM");

void TransformComponent::calculateCenter()
{
    m_center = Vector2(m_position.getX() + (m_scale.getX() / 2), m_position.getY() + (m_scale.getY() / 2));
}

void TransformComponent::updateChildTransforms()
{
    if (_childTransforms.size() <= 0) return;
    
    for (auto transform : _childTransforms)
    {
        if (transform) 
        {
            Vector2 localPos = transform->getLocalPosition();
            transform->setLocalPosition(localPos);
        }
    }
}

void TransformComponent::translate(const Vector2& pos)
{
    m_position.add(pos);
}
void TransformComponent::translate(float x, float y)
{
    m_position.add(x, y);
}

void TransformComponent::setPosition(const Vector2& pos)
{
    m_position.set(pos);
    if (_parentTransform) m_localPosition =_parentTransform->getPosition() - m_position;
    else m_localPosition = m_position;

    calculateCenter();
    updateChildTransforms();
}
void TransformComponent::setPosition(float x, float y)
{
    m_position.set(x, y);
    if (_parentTransform) m_localPosition =_parentTransform->getPosition() - m_position;
    else m_localPosition = m_position;

    calculateCenter();
    updateChildTransforms();
}
void TransformComponent::setLocalPosition(const Vector2& pos)
{
    m_localPosition.set(pos);
    if (_parentTransform) m_position = m_localPosition + _parentTransform->getPosition();
    else m_position = m_localPosition;

    calculateCenter();
    updateChildTransforms();
}
void TransformComponent::setLocalPosition(float x, float y)
{
    m_localPosition.set(x, y);
    if (_parentTransform) m_position = m_localPosition + _parentTransform->getPosition();
    else m_position = m_localPosition;
    
    calculateCenter();
    updateChildTransforms();
}
const Vector2& TransformComponent::getPosition()const
{
    return m_position;
}
const Vector2& TransformComponent::getLocalPosition()const
{
    return m_localPosition;
}
const Vector2& TransformComponent::getPositionCentered() const
{
    return m_center;
}

void TransformComponent::setScale(const Vector2& scale)
{
    m_scale.set(scale);
    calculateCenter();
}
void TransformComponent::setScale(float x, float y)
{
    m_scale.set(x, y);
    calculateCenter();
}
const Vector2& TransformComponent::getScale() const
{
    return m_scale;
} 

void TransformComponent::attachChild(std::shared_ptr<TransformComponent> child)
{
    if (child) _childTransforms.emplace_back(child);
}


std::string TransformComponent::toString()
{
    std::ostringstream s;
    s << "Transform: {" << " pos={" << m_position << "}, size={" << m_scale << "}";
    std::string str = s.str();
    
    return str;
}
