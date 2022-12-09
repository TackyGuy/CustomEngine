#pragma once

#include "SDL.h"
#include "SDL_image.h"

#include "renderercomponent.h"
#include "spritesheetasset.h"
#include "sprite.h"


#include <iostream>
#include <vector>

namespace Core
{
    class SpriteRendererComponent: public RendererComponent
    {
        private:
            Sprite *m_sprite = nullptr;
            SDL_Rect m_rect;
            bool m_flipX = false;

        public:
            static const size_t Type;

            ~SpriteRendererComponent(){}
            SpriteRendererComponent(BroadcasterInterface *broadcaster, Sprite *sprite)
            : RendererComponent(broadcaster), m_sprite(sprite)
            {
                m_rect.x = 0;
                m_rect.y = 0;
                m_rect.w = 32;
                m_rect.h = 32;
            }
            SpriteRendererComponent(BroadcasterInterface *broadcaster, Sprite *sprite, SDL_Rect rect)
            : RendererComponent(broadcaster), m_sprite(sprite), m_rect(rect)
            {}
            SpriteRendererComponent(BroadcasterInterface *broadcaster, const SpriteRendererComponent& sr)
            : RendererComponent(broadcaster), m_sprite(sr.m_sprite), m_rect(sr.m_rect)
            {}

            void render(SDL_Renderer *renderer, const Vector2& pos, const Vector2& size) override
            {
                SDL_Rect src = 
                {
                    m_sprite->getRect().x,
                    m_sprite->getRect().y,
                    m_sprite->getRect().w,
                    m_sprite->getRect().h
                };
                SDL_Rect dst = 
                {
                    (int)pos.getX(),
                    (int)pos.getY(),
                    (int)size.getX(),
                    (int)size.getY()
                };
                // std::cout << "Rect: x=" << pos.getX() << "y=" << pos.getY() << "w=" << size.getX() << "h=" << size.getY() 
                // << std::endl;
                
                if (m_sprite->getTexture() != nullptr)
                {
                    if (SDL_RenderCopyEx(renderer, m_sprite->getTexture(), &src, &dst, 0, NULL, (m_flipX)? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE) != 0) 
                        std::cout << "[SpriteRenderer] SDL:" << SDL_GetError() << std::endl;
                }
                
            }

            void setSprite(Sprite *sprite);
            Sprite& getSprite();
            SDL_Rect getRect();
            void flip(bool val);
            bool getFlip() const;
    };
}