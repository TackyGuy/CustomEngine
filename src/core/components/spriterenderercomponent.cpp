#include "spriterenderercomponent.h"
using namespace Core;


const size_t SpriteRendererComponent::Type = std::hash<std::string>{}("Renderer");

SDL_Rect SpriteRendererComponent::getRect()
{
    if (m_sprite == nullptr) return m_rect;
    return m_sprite->getRect();
}

void SpriteRendererComponent::setSprite(Sprite *sprite)
{
    m_sprite = sprite;
}
Sprite& SpriteRendererComponent::getSprite()
{
    return *m_sprite;
}

void SpriteRendererComponent::flip(bool val)
{
    m_flipX = val;
}

bool SpriteRendererComponent::getFlip() const
{
    return m_flipX;
}