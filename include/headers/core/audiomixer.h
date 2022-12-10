#pragma once

#include "SDL_mixer.h"
#include "audioasset.h"

namespace Core
{
    class AudioMixer
    {
        private:
            uint16_t m_volume = 0;
            AudioAsset *_currentMusic = nullptr;
        public:
            ~AudioMixer()
            {
                if (!_currentMusic) Mix_FreeMusic(_currentMusic->getMusic());
            }
            AudioMixer(int volume = 80) : m_volume(volume)
            {

            }

            void setVolume(uint16_t volume);
            const int getVolume() const;

            void playMusic(AudioAsset *music);
            void playSound(AudioAsset *sound);

            void togglePlay();


    };
}