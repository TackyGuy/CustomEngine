#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "SDL_image.h"

#include "asset.hpp"
#include "sprite.hpp"

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
            bool m_vertical;
        public:

            ~SpritesheetAsset()
            {
                SDL_DestroyTexture(_texture);
            };
            /**
             * @brief Construct a new Spritesheet Asset object.
             * 
             * @param path The path of this Asset
             * @param width The desired width of an individual sprite in this sheet
             * @param height The desired height of an individual sprite in this sheet
             * @param limit How many sprites should be created off of this sheet
             * @param isVertical If this spritesheet should be sliced vertically first
             */
            SpritesheetAsset(const char* path, uint16_t width, uint16_t height, uint16_t limit = 0, bool isVertical = false)
            : Asset(path), m_width(width), m_height(height), m_limit(limit), m_vertical(isVertical)
            {
                std::cout<< "\nCreating new spritesheet..." << std::endl;
            }

            /**
             * @brief Get the Type of this Asset.
             * 
             * @return size_t 
             */
            size_t getType()
            {
                return std::hash<std::string>{}("Spritesheet");
            };

            /**
             * @brief Create the SDL_Texture and splice the spritesheet accordingly.
             * 
             */
            void initTexture();
            /**
             * @brief Set the Texture of this spritesheet.
             * 
             * @param tex A pointer to the texture
             */
            void setTexture(SDL_Texture *tex);
            /**
             * @brief Returns the Texture of this spritesheet.
             * 
             * @return SDL_Texture* pointer to the texture
             */
            SDL_Texture *getTexture();

            /**
             * @brief Returns the Sprite object at the designated index.
             * 
             * @param index The index of the desired Sprite Object
             * @return std::shared_ptr<Sprite> a shared_ptr to the Sprite
             */
            std::shared_ptr<Sprite> getSpriteAt(const uint16_t& index);
            /**
             * @brief Returns the All the Sprite objects in this spritesheet.
             * 
             * @return std::vector<std::shared_ptr<Sprite>> A vector with shared_ptr to the Sprite objects
             */
            std::vector<std::shared_ptr<Sprite>> getAllSprites();
            /**
             * @brief Returns the number of Sprite objects this spritesheet holds.
             * 
             * @return uint16_t Count of Sprite objects
             */
            uint16_t getSpriteCount();
    };
}