#pragma once

#include <iostream>

#include "SDL_mixer.h"
#include "audioasset.h"

namespace Core
{
    class AudioMixer
    {
        private:
            int m_volume = 0;
            AudioAsset *_currentMusic = nullptr;
        public:
            ~AudioMixer()
            {
                if (!_currentMusic) Mix_FreeMusic(_currentMusic->getMusic());
            }
            AudioMixer(int volume = 5) : m_volume(volume)
            {

            }

            void setVolume(int volume);
            const int getVolume() const;

            void playMusic(AudioAsset *music);
            void playSound(AudioAsset *sound);

            void togglePlay();


    };
}