#include "asset.h"
using namespace Core;

const size_t Asset::SpritesheetType = std::hash<std::string>{}("Spritesheet");
const size_t Asset::AudioAssetType = std::hash<std::string>{}("Audio");
const size_t Asset::FontAssetType = std::hash<std::string>{}("Font");
const size_t Asset::NullType = std::hash<std::string>{}("Null");


void Asset::setLoaded(bool value)
{
    m_loaded = value;
}
bool Asset::isLoaded()
{
    return m_loaded;
}

void Asset::setPath(const char *path)
{
    _textPath = path;
}

const char* Asset::getPath()
{
    return _textPath;
}