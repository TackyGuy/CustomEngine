#pragma once

#include "SDL.h"
#include "basecomponent.h"
#include "mathutils.h"

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

            virtual ~RendererComponent(){}
            /**
             * @brief Construct a new Renderer Component object.
             * 
             * @param p_broadcaster The actor that implements the IBroadcaster interface
             */
            RendererComponent(const BroadcasterInterface& p_broadcaster) : BaseComponent(p_broadcaster){};

            /**
             * @brief Renders this component at the selected position and with the desired size
             * 
             * @param renderer SDL_Renderer
             * @param pos Vector2
             * @param size Vector2
             */
            virtual void render(SDL_Renderer *renderer, const Vector2& pos, const Vector2& size){};         
    };
}