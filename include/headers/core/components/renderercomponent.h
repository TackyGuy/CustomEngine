#pragma once

#include "SDL.h"
#include "basecomponent.h"
#include "math.h"

namespace Core
{
    class RendererComponent: public BaseComponent
    {
        private:
            int m_layer = 0;
        public:
            static const size_t Type;
            const size_t getType() const override
            {
                return Type;
            }

            ~RendererComponent(){}
            RendererComponent(const BroadcasterInterface& p_broadcaster) : BaseComponent(p_broadcaster){};

            virtual void render(SDL_Renderer *renderer, const Vector2& pos, const Vector2& size){};         
    };
}