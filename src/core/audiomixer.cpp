#include "audiomixer.h"
using namespace Core;

void AudioMixer::setVolume(int volume)
{
    m_volume = (MIX_MAX_VOLUME * volume) / 100;
}
const int AudioMixer::getVolume() const
{
    return m_volume;
}

void AudioMixer::playMusic(AudioAsset *music)
{
    _currentMusic = music;
    Mix_VolumeMusic(m_volume);
    Mix_PlayMusic(_currentMusic->getMusic(), -1);
}
void AudioMixer::playSound(AudioAsset *sound)
{
    // int channel =  Mix_PlayChannel(-1, sound->getMusic());
    // Mix_Volume(channel, m_volume);
}

void AudioMixer::togglePlay()
{
    if (Mix_PausedMusic()) Mix_ResumeMusic();
    else Mix_PauseMusic();
}