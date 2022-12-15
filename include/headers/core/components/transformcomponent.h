#pragma once

#include "../math.h"

#include "basecomponent.h"

#include <iostream>
#include <string.h>
#include <sstream>

namespace Core
{
    class TransformComponent: public BaseComponent
    {
        private:
            Vector2 _position;
            Vector2 _scale;
            Vector2 _center;

            void calculateCenter();
        public:
            static const size_t Type;
            const size_t getType() const override
            {
                return Type;
            }

            ~TransformComponent(){}
            TransformComponent(const BroadcasterInterface& p_broadcaster) :BaseComponent(p_broadcaster)
            {
                _position = Vector2(0, 0);
                _scale = Vector2(0, 0);
                _center = Vector2(0, 0);
            }
            TransformComponent(const BroadcasterInterface& p_broadcaster, const Vector2& pos, const Vector2& scale)
            : BaseComponent(p_broadcaster), _position(pos), _scale(scale)
            {
                calculateCenter();
            }
            TransformComponent(const BroadcasterInterface& p_broadcaster, const TransformComponent& transform)
            : BaseComponent(p_broadcaster), _position(transform._position), _scale(transform._scale), _center(transform._center)
            {}

            void translate(const Vector2& pos);
            void translate(float x, float y);

            void setPosition(const Vector2& pos);
            void setPosition(float x, float y);
            const Vector2& getPosition() const;
            const Vector2& getPositionCentered() const;
            
            void setScale(const Vector2& scale);
            void setScale(float x, float y);
            const Vector2& getScale() const;

            std::string toString();
    };
}