#pragma once

#include "SDL_image.h"

#include <iostream>
#include <string>

namespace Core
{
    class Sprite
    {
        private:
            SDL_Texture *_tex = nullptr;

            SDL_Rect m_rect{0, 0, 0, 0};
            bool m_keepRatio;
        public:
            ~Sprite(){};
            
            Sprite(const Sprite& sprite) : m_rect(sprite.m_rect){}

            Sprite(SDL_Texture *texture, SDL_Rect rect, bool keepRatio = true) : _tex(texture), m_rect(rect), m_keepRatio(keepRatio){}
            
            SDL_Rect getRect();
            void setRect(int x, int y, int w, int h);

            SDL_Texture *getTexture();
            const bool isKeepRatio() const;
    };
}