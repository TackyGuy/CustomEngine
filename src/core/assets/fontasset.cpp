#include "fontasset.h"
using namespace Core;

void FontAsset::setFont(TTF_Font *font)
{
    _font = font;
}
TTF_Font *FontAsset::getFont()
{
    return _font;
}
const int FontAsset::getSize() const
{
    return size;
}
