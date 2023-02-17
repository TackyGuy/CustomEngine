#include "spriterenderercomponent.hpp"
using namespace Core;


const size_t SpriteRendererComponent::Type = std::hash<std::string>{}("Renderer");

SDL_Rect SpriteRendererComponent::getRect()
{
    if (_sprite) _sprite->getRect();
    
    return m_rect;
}

void SpriteRendererComponent::setSprite(std::shared_ptr<Sprite> sprite)
{
    if (sprite) _sprite = sprite;
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