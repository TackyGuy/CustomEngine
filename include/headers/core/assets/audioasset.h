#pragma once

#include "SDL_mixer.h"
#include "asset.h"

namespace Core
{
    class AudioAsset: public Asset
    {
        private:
            const char *p_textPath;
            Mix_Music *_music = nullptr;
            Mix_Chunk *_sound = nullptr;
            bool m_isMusic;
        public:
            ~AudioAsset(){};

            AudioAsset(const char *p_path, bool music)
            : Asset(p_path), m_isMusic(music)
            {}
            
            size_t getType()
            {
                return std::hash<std::string>{}("Audio");
            };

            void setAudio(Mix_Chunk *sound, Mix_Music *music);
            Mix_Music *getMusic();
            Mix_Chunk *getSoundChunk();

            const bool isMusic() const;
    };
}