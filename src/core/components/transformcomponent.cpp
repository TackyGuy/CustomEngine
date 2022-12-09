#include "transformcomponent.h"
using namespace Core;

const size_t TransformComponent::Type = std::hash<std::string>{}("TRANSFORM");

void TransformComponent::calculateCenter()
{
    _center = Vector2(_position.getX() + (_scale.getX() / 2), _position.getY() + (_scale.getY() / 2));
}

void TransformComponent::translate(const Vector2& pos)
{
    _position.add(pos);
}
void TransformComponent::translate(float x, float y)
{
    _position.add(x, y);
}

void TransformComponent::setPosition(const Vector2& pos)
{
    _position.set(pos);
    calculateCenter();
}
void TransformComponent::setPosition(float x, float y)
{
    _position.set(x, y);
}
const Vector2& TransformComponent::getPosition()const
{
    return _position;
}
const Vector2& TransformComponent::getPositionCentered() const
{
    return _center;
}

void TransformComponent::setScale(const Vector2& scale)
{
    _scale.set(scale);
    calculateCenter();
}
void TransformComponent::setScale(float x, float y)
{
    _scale.set(x, y);
    calculateCenter();
}
const Vector2& TransformComponent::getScale() const
{
    return _scale;
} 

std::string TransformComponent::toString()
{
    std::ostringstream s;
    s << "Transform: {" << " pos={" << "x: " << _position.getX() << ", y: " << _position.getY() << "}, size={" << "x: " << _scale.getX() << ", y: " << _scale.getY() << "}";
    std::string str = s.str();
    
    return str;
}
