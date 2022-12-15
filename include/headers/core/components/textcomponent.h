#pragma once

#include "SDL_ttf.h"
#include <string>
#include <sstream>
#include <cmath>

#include "math.h"
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
            FontAsset *_font = nullptr;

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
                SDL_DestroyTexture(_texture);
            }
            TextComponent(const BroadcasterInterface& p_broadcaster, const char* str, SDL_Color colour, FontAsset *font): RendererComponent(p_broadcaster), m_text(str), m_colour(colour), _font(font)
            {
                createSurface();
            }

            virtual void update (double dt, Stage& stage) override
            {
                
            }

            virtual void render(SDL_Renderer *renderer, const Vector2& pos, const Vector2& size) override
            {
                if (m_dirty) setTexture(SDL_CreateTextureFromSurface(renderer, _surface));

                if (_texture == nullptr) return;
                // if (sprite == nullptr) std:: cout << "sprite invalid" << std::endl;
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

            void setText(std::string& text);
            std::string& getText();

            SDL_Color& getColor();
            void setColour(SDL_Color& colour);

            void setFont(FontAsset *font);
            SDL_Surface *getSurface();

            void setTexture(SDL_Texture * texture);
            SDL_Texture *getTexture();
    };
}