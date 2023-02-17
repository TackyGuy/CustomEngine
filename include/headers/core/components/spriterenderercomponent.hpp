#pragma once

#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"

#include "renderercomponent.hpp"
#include "spritesheetasset.hpp"
#include "mathutils.hpp"
#include "sprite.hpp"

namespace Core
{
    class SpriteRendererComponent: public RendererComponent
    {
        private:
            std::shared_ptr<Sprite> _sprite = nullptr;
            SDL_Rect m_rect{0, 0, 0, 0};
            bool m_flipX = false;

        public:
            static const size_t Type;
            const size_t getType() const override
            {
                return Type;
            }

            ~SpriteRendererComponent(){}
            /**
             * @brief Construct a new SpriteRendererComponent object.
             * 
             * @param actor The actor that implements the IBroadcaster interface
             * @param sprite shared_ptr to the Sprite this spriterenderer should hold
             */
            SpriteRendererComponent(const ActorInterface& actor, std::shared_ptr<Sprite> sprite)
            : RendererComponent(actor), _sprite(sprite)
            {
                m_rect.x = 0;
                m_rect.y = 0;
                m_rect.w = 32;
                m_rect.h = 32;
            }
            /**
             * @brief Construct a new SpriteRendererComponent object.
             * 
             * @param actor The actor that implements the IBroadcaster interface
             * @param sprite shared_ptr to the Sprite this spriterenderer should hold
             * @param rect The Rect of the Sprite
             */
            SpriteRendererComponent(const ActorInterface& actor, std::shared_ptr<Sprite> sprite, SDL_Rect rect)
            : RendererComponent(actor), _sprite(sprite), m_rect(rect)
            {}
            /**
             * @brief Construct a new SpriteRendererComponent object by copy.
             * 
             * @param actor The actor that implements the IBroadcaster interface
             * @param sr The SpriteRenderComponent to copy
             */
            SpriteRendererComponent(const ActorInterface& actor, const SpriteRendererComponent& sr)
            : RendererComponent(actor), _sprite(sr._sprite), m_rect(sr.m_rect)
            {}

            SpriteRendererComponent(SpriteRendererComponent& other) = default;
            SpriteRendererComponent(SpriteRendererComponent&& other):
                RendererComponent(other.actorInterface)
            {
                _sprite = other._sprite;
                m_rect = other.m_rect;
                m_flipX = other.m_flipX;

                other._sprite = nullptr;
            }

            void render(SDL_Renderer *renderer, const Vector2& pos, const Vector2& size) override
            {
                if (!renderer) return;
                if (!_sprite) return;
                
                SDL_Rect src = 
                {
                    _sprite->getRect().x,
                    _sprite->getRect().y,
                    _sprite->getRect().w,
                    _sprite->getRect().h
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
                
                if (_sprite->getTexture() != nullptr)
                {
                    if (SDL_RenderCopyEx(renderer, _sprite->getTexture(), &src, &dst, 0, NULL, (m_flipX)? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE) != 0) 
                        std::cout << "[SpriteRenderer] SDL:" << SDL_GetError() << std::endl;
                }
                
            }

            /**
             * @brief Set the Sprite object to a new Sprite.
             * 
             * @param sprite A shared_ptr to the new Sprite
             */
            void setSprite(std::shared_ptr<Sprite> sprite);
            /**
             * @brief Returns a reference to the current Sprite object.
             * 
             * @return Sprite& The Sprite to return
             */
            Sprite& getSprite();
            /**
             * @brief Returns the Rect of this Sprite.
             * 
             * @return SDL_Rect 
             */
            SDL_Rect getRect();
            /**
             * @brief Flips the SpriteRendererComponent horizontally.
             * 
             * @param val 
             */
            void flip(bool val);
            /**
             * @brief Is the spriterenderer flipped?
             * 
             * @return true if it is
             * @return false if it's not
             */
            bool getFlip() const;
    };
}