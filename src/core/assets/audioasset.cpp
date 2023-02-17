#include "audioasset.hpp"
using namespace Core;

void AudioAsset::setAudio(Mix_Chunk *sound, Mix_Music *music)
{
    if (sound) 
    {
        _sound = sound;
        return;
    }
    if (music) 
    {
        _music = music;
        return;
    }
}

Mix_Music *AudioAsset::getMusic()
{
    return _music;
}
Mix_Chunk *AudioAsset::getSoundChunk()
{
    return _sound;
}

const bool AudioAsset::isMusic() const
{
    return m_isMusic;
}
