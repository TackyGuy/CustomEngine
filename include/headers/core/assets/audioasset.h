#pragma once

#include "SDL_mixer.h"
#include "asset.h"

namespace Core
{
    class AudioAsset: public Asset
    {
        private:
            const char *p_textPath;
            Mix_Music *_file = nullptr;
        public:
            ~AudioAsset(){};

            AudioAsset(const char *p_path)
            : Asset(p_path)
            {}
            
            size_t getType()
            {
                return std::hash<std::string>{}("Audio");
            };
            
            void setMusic(Mix_Music *music);
            Mix_Music *getMusic();
    };
}