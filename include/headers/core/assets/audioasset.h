#pragma once

#include "SDL_mixer.h"
#include "asset.h"

namespace Core
{
    class AudioAsset: public Asset
    {
        private:
            Mix_Music *_music = nullptr;
            Mix_Chunk *_sound = nullptr;
            bool m_isMusic;
        public:
            ~AudioAsset()
            {
                if (!_music) Mix_FreeMusic(_music);
                if (!_sound) Mix_FreeChunk(_sound);
            };

            /**
             * @brief Construct a new AudioAsset.
             * 
             * @param path The path of this asset
             * @param music Is this AudioAsset a music track?
             */
            AudioAsset(const char *path, bool music)
            : Asset(path), m_isMusic(music)
            {}
            
            /**
             * @brief Returns the Type of this Asset.
             * 
             * @return size_t 
             */
            size_t getType()
            {
                return std::hash<std::string>{}("Audio");
            };

            /**
             * @brief Set the Audio of this AudioAsset.
             * 
             * @param sound The sound effect associated with this AudioAsset
             * @param music The music track associated with this AudioAsset
             */
            void setAudio(Mix_Chunk *sound, Mix_Music *music);
            /**
             * @brief Returns the music.
             * 
             * @return Mix_Music* 
             */
            Mix_Music *getMusic();
            /**
             * @brief Returns the sound effect.
             * 
             * @return Mix_Chunk* 
             */
            Mix_Chunk *getSoundChunk();

            /**
             * @brief Is this AudioAsset a music track?
             * 
             * @return true if it is a music track
             * @return false if it is not a music track
             */
            const bool isMusic() const;
    };
}