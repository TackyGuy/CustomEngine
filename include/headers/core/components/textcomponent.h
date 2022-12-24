#pragma once

#include "SDL_ttf.h"
#include <string>
#include <sstream>
#include <cmath>

#include "mathutils.h"
#include "renderercomponent.h"
#include "fontasset.h"

namespace Core
{
    class TextComponent: public RendererComponent
    {
        private:
            std::string m_text;
            SDL_Color m_colour;

            SDL_Surface *_surface = nullptr;
            SDL_Texture *_texture = nullptr;
            std::shared_ptr<FontAsset> _fontAsset = nullptr;

            bool m_dirty = true;

            void createSurface();
        public:
            static const size_t Type;
            const size_t getType() const override
            {
                return Type;
            }

            ~TextComponent()
            {
                SDL_FreeSurface(_surface);
                SDL_DestroyTexture(_texture);
            }
            /**
             * @brief Construct a new TextComponent object.
             * 
             * @param p_broadcaster The actor that implements the IBroadcaster interface
             * @param str The text this TextComponent should hold
             * @param colour The colour of the text
             * @param font The font in which the text should be written
             */
            TextComponent(const BroadcasterInterface& p_broadcaster, const char *str, SDL_Color colour, std::shared_ptr<FontAsset> font): 
                RendererComponent(p_broadcaster), m_text(str), m_colour(colour), _fontAsset(font)
            {
                createSurface();
            }

            TextComponent(TextComponent& other) = default;
            TextComponent(TextComponent&& other):
                RendererComponent(other.broadcaster)
            {
                m_text = other.m_text;
                m_colour = other.m_colour;
                _surface = other._surface;

                _fontAsset = other._fontAsset;
                m_dirty = true;

                other._surface = nullptr;
                other._texture = nullptr;

                createSurface();
            }

            virtual void update (double dt, Stage& stage) override
            {
                
            }

            virtual void render(SDL_Renderer *renderer, const Vector2& pos, const Vector2& size) override
            {
                if (!renderer) return;

                if (m_dirty) setTexture(SDL_CreateTextureFromSurface(renderer, _surface));

                if (!_texture) 
                {
                    m_dirty = true;
                    return;
                }
                int texW = 0;
                int texH = 0;
                if (SDL_QueryTexture(_texture, NULL, NULL, &texW, &texH) != 0) std::cout << SDL_GetError() << std::endl;
                SDL_Rect src 
                {
                    0,
                    0,
                    texW,
                    texH
                };

                SDL_Rect dst
                {
                    (int)pos.getX(),
                    (int)pos.getY(),
                    (int)(size.getX() * texW * 0.1f),
                    (int)(size.getY() * texH * 0.1f)
                };
                
                if (SDL_RenderCopy(renderer, _texture, &src, &dst) != 0) std::cout << "SDL:" << SDL_GetError() << std::endl;
            }

            /**
             * @brief Set the Text to a new string.
             * 
             * @param text The new text
             */
            void setText(std::string& text);
            /**
             * @brief Returns the text of this textcomponent.
             * 
             * @return std::string& The text
             */
            std::string& getText();

            /**
             * @brief Set the colour of this textcomponent to a new one.
             * 
             * @param colour The new SDL_Colour
             */
            void setColour(SDL_Color& colour);
            /**
             * @brief Get the Color object
             * 
             * @return SDL_Color& 
             */
            SDL_Color& getColor();

            /**
             * @brief Set the Font of this textcomponent to a new one.
             * 
             * @param font The new FontAsset
             */
            void setFont(std::shared_ptr<FontAsset> font);
            /**
             * @brief Returns the SDL_Surface held by textcomponent.
             * 
             * @return SDL_Surface* A pointer to the surface
             */
            SDL_Surface *getSurface();

            /**
             * @brief Set the texture of this textcomponent to a new one.
             * 
             * @param texture The new SDL_Texture
             */
            void setTexture(SDL_Texture *texture);
            /**
             * @brief Returns the current texture of this textcomponent.
             * 
             * @return SDL_Texture* A pointer to the current texture
             */
            SDL_Texture *getTexture();
    };
}