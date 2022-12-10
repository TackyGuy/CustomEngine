#include "audioasset.h"
using namespace Core;

void AudioAsset::setMusic(Mix_Music *music)
{
    _file = music;
}
Mix_Music *AudioAsset::getMusic()
{
    return _file;
}
