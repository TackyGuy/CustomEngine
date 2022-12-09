#include "fontasset.h"
using namespace Core;

void FontAsset::setSize(uint16_t size)
{
    m_size = size;
}
uint16_t FontAsset::getSize()
{
    return m_size;
}

void FontAsset::setFont(TTF_Font *font)
{
    p_font = font;
}
TTF_Font *FontAsset::getFont()
{
    return p_font;
}
