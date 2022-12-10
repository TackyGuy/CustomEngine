#include "audiomixer.h"
using namespace Core;

void AudioMixer::setVolume(uint16_t volume)
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
    Mix_Volume(1, m_volume);
    Mix_PlayMusic(_currentMusic->getMusic(), 0);
}
void AudioMixer::playSound(AudioAsset *sound)
{

}

void AudioMixer::togglePlay()
{
    if (Mix_PausedMusic()) Mix_ResumeMusic();
    else Mix_PauseMusic();
}