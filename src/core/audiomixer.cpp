#include "audiomixer.hpp"
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
    if (!m_canPlay) return;
    
    _currentMusic = music;
    Mix_VolumeMusic(m_musicVolume);
    Mix_PlayMusic(_currentMusic->getMusic(), -1);
}
void AudioMixer::playSound(std::shared_ptr<AudioAsset> sound, double t)
{
    if (!m_canPlay) return;
    if (t + soundDelay < m_lastPlayedSound) return;
    
    int channel =  Mix_PlayChannel(-1, sound->getSoundChunk(), 0);
    Mix_Volume(channel, m_soundVolume);
    std::cout << Mix_GetError() << std::endl;
    m_lastPlayedSound = t;
}

void AudioMixer::togglePlay()
{
    if (!m_canPlay) 
    {
        Mix_ResumeMusic();
        m_canPlay = true;
    }
    else 
    {
        Mix_PauseMusic();
        m_canPlay = false;
    }
}
void AudioMixer::togglePlay(bool val)
{
    if (val)
    {
        Mix_ResumeMusic();
        m_canPlay = true;
    }
    else 
    {
        Mix_PauseMusic();
        m_canPlay = false;
    }
}

const bool AudioMixer::isPlaying() const
{
    return m_canPlay;
}