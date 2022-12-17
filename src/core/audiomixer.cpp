#include "audiomixer.h"
using namespace Core;

void AudioMixer::setMusicVolume(int volume)
{
    m_musicVolume = (MIX_MAX_VOLUME * volume) / 100;
}
const int AudioMixer::getMusicVolume() const
{
    return m_musicVolume;
}
void AudioMixer::setSoundVolume(int volume)
{
    m_soundVolume = (MIX_MAX_VOLUME * volume) / 100;
}
const int AudioMixer::getSoundVolume() const
{
    return m_soundVolume;
}

void AudioMixer::playMusic(std::shared_ptr<AudioAsset> music)
{
    _currentMusic = music;
    Mix_VolumeMusic(m_musicVolume);
    Mix_PlayMusic(_currentMusic->getMusic(), -1);
}
void AudioMixer::playSound(std::shared_ptr<AudioAsset> sound)
{
    int channel =  Mix_PlayChannel(-1, sound->getSoundChunk(), 0);
    Mix_Volume(channel, m_soundVolume);
}

void AudioMixer::togglePlay()
{
    if (Mix_PausedMusic()) Mix_ResumeMusic();
    else Mix_PauseMusic();
}