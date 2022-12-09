#include "textcomponent.h"
using namespace Core;

const size_t TextComponent::Type = std::hash<std::string>{}("Text");

void TextComponent::createSurface()
{
    SDL_FreeSurface(_surface);
    _surface = TTF_RenderText_Solid(_font->getFont(), m_text.c_str(), m_colour);
    m_dirty = true;
}

void TextComponent::setText(std::string& text)
{
    m_text = text;
    createSurface();
}

std::string& TextComponent::getText()
{
    return m_text;
}     

void TextComponent::setColour(SDL_Color& colour)
{
    m_colour = colour;
    createSurface();
}

SDL_Color& TextComponent::getColor()
{
    return m_colour;
}

void TextComponent::setFont(FontAsset *font)
{
    _font = font;
    createSurface();
}
SDL_Surface *TextComponent::getSurface()
{
    return _surface;
}

void TextComponent::setTexture(SDL_Texture * texture)
{
    SDL_DestroyTexture(_texture);
    _texture = texture;
    // We set the dirty flag to false
    m_dirty = false;
}
SDL_Texture *TextComponent::getTexture()
{
    return _texture;
}
