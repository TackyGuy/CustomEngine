#include "sprite.h"
using namespace Core;

SDL_Rect Sprite::getRect()
{
    return m_rect;
}
void Sprite::setRect(int x, int y, int w, int h)
{
    SDL_Rect rect = {x, y, w, h};
    m_rect = rect;
}

SDL_Texture *Sprite::getTexture()
{
    return _tex;
}

const bool Sprite::isKeepRatio() const
{
    return m_keepRatio;
}