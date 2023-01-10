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
            std::shared_ptr<AudioAsset> _currentMusic = nullptr;
        public:
            ~AudioMixer(){};
            /**
             * @brief Construct a new Audio Mixer object
             * 
             * @param volume The base volume
             */
            AudioMixer(int volume = 5) : m_musicVolume(volume), m_soundVolume(volume)
            {

            }

            /**
             * @brief Set the volume of the music
             * 
             * @param volume The volume
             */
            void setMusicVolume(int volume);
            /**
             * @brief Get the volume of the music
             * 
             * @return const int 
             */
            const int getMusicVolume() const;
            /**
             * @brief Set the volume of the sound effects
             * 
             * @param volume 
             */
            void setSoundVolume(int volume);
            /**
             * @brief Get volume of the sound effects
             * 
             * @return const int 
             */
            const int getSoundVolume() const;

            /**
             * @brief Plays the selected AudioAsset as music
             * 
             * @param music The music to play
             */
            void playMusic(std::shared_ptr<AudioAsset> music);
            /**
             * @brief Plays the selected AudioAsset as a sound effect
             * 
             * @param music The sound effect to play
             */
            void playSound(std::shared_ptr<AudioAsset> sound);

            /**
             * @brief Toggle the mixer between the pause and play states
             * 
             */
            void togglePlay();

            /**
             * @brief Check if the mixer is currently playing
             * 
             */
            const bool isPlaying() const;


    };
}