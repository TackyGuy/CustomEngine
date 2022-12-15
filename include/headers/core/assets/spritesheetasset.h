#pragma once

#include "asset.h"
#include "sprite.h"

#include "SDL_image.h"
#include <vector>
#include <string>

#include <iostream>

namespace Core
{
    class SpritesheetAsset: public Asset
    {
        private:
            SDL_Texture *_texture = nullptr;

            uint16_t m_width;
            uint16_t m_height;
            uint16_t m_limit;

            std::vector<std::shared_ptr<Sprite>> _sprites;
            uint16_t m_currentSpriteIndex = 0;
            bool m_vertical;
        public:

            ~SpritesheetAsset()
            {
                SDL_DestroyTexture(_texture);
            };
            SpritesheetAsset(const char* path, uint16_t width, uint16_t height, uint16_t limit = 0, bool isVertical = false)
            : Asset(path), m_width(width), m_height(height), m_limit(limit), m_vertical(isVertical)
            {
                std::cout<< "\nCreating new spritesheet..." << std::endl;
            }

            size_t getType()
            {
                return std::hash<std::string>{}("Spritesheet");
            };

            
            void initTexture();
            void setTexture(SDL_Texture *tex);
            SDL_Texture *getTexture();

            std::shared_ptr<Sprite> getSpriteAt(const uint16_t& index);
            std::shared_ptr<Sprite> getCurrentSprite();
            std::vector<std::shared_ptr<Sprite>> getAllSprites();
            uint16_t getCurrentSpriteID();
            uint16_t getSpriteCount();
            void setCurrentSprite(const uint16_t& index); 
    };
}