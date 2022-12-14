#pragma once

#include <iostream>

#include "SDL_mixer.h"
#include "audioasset.h"

namespace Core
{
    class AudioMixer
    {
        private:
            uint16_t m_musicVolume = 0;
            uint16_t m_soundVolume = 0;
            AudioAsset *_currentMusic = nullptr;
        public:
            ~AudioMixer()
            {
                if (!_currentMusic) Mix_FreeMusic(_currentMusic->getMusic());
            }
            AudioMixer(int volume = 5) : m_musicVolume(volume), m_soundVolume(volume)
            {

            }

            void setMusicVolume(int volume);
            const int getMusicVolume() const;
            void setSoundVolume(int volume);
            const int getSoundVolume() const;

            void playMusic(AudioAsset *music);
            void playSound(AudioAsset *sound);

            void togglePlay();


    };
}