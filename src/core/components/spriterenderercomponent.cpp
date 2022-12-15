#include "spriterenderercomponent.h"
using namespace Core;


const size_t SpriteRendererComponent::Type = std::hash<std::string>{}("Renderer");

SDL_Rect SpriteRendererComponent::getRect()
{
    if (_sprite == nullptr) return m_rect;
    return _sprite->getRect();
}

void SpriteRendererComponent::setSprite(std::shared_ptr<Sprite> sprite)
{
    _sprite = sprite;
}
Sprite& SpriteRendererComponent::getSprite()
{
    return *_sprite;
}

void SpriteRendererComponent::flip(bool val)
{
    m_flipX = val;
}

bool SpriteRendererComponent::getFlip() const
{
    return m_flipX;
}