#pragma once

#include "mathutils.h"

#include "basecomponent.h"

#include <iostream>
#include <vector>
#include <string.h>
#include <sstream>

namespace Core
{
    class TransformComponent: public BaseComponent
    {
        private:
            Vector2 m_position;
            Vector2 m_localPosition;
            Vector2 m_scale;
            Vector2 m_localScale;
            Vector2 m_center;

            std::shared_ptr<TransformComponent> _parentTransform = nullptr;
            std::vector<std::shared_ptr<TransformComponent>> _childTransforms;

            void calculateCenter();
            void updateChildTransforms();
        public:
            static const size_t Type;
            const size_t getType() const override
            {
                return Type;
            }

            ~TransformComponent(){}
            /**
             * @brief Construct a new Transform Component object with every members holding a Vector2(0, 0).
             * 
             * @param p_broadcaster The actor that implements the IBroadcaster interface
             */
            TransformComponent(const BroadcasterInterface& p_broadcaster, std::shared_ptr<TransformComponent> parent) :BaseComponent(p_broadcaster)
            {
                _parentTransform = parent;
                m_position = Vector2(0, 0);
                m_scale = Vector2(0, 0);
                m_center = Vector2(0, 0);
            }
            /**
             * @brief Construct a new Transform Component object.
             * 
             * @param p_broadcaster The actor that implements the IBroadcaster interface
             * @param pos The position
             * @param scale The scale
             */
            TransformComponent(const BroadcasterInterface& p_broadcaster, const Vector2& pos, const Vector2& scale, std::shared_ptr<TransformComponent> parent)
            : BaseComponent(p_broadcaster), m_position(pos), m_scale(scale)
            {
                _parentTransform = parent;
                calculateCenter();
            }
            /**
             * @brief Construct a new Transform Component object.
             * 
             * @param p_broadcaster The actor that implements the IBroadcaster interface
             * @param transform The TransformComponent to copy
             */
            TransformComponent(const BroadcasterInterface& p_broadcaster, const TransformComponent& transform)
            : BaseComponent(p_broadcaster), m_position(transform.m_position), m_scale(transform.m_scale), m_center(transform.m_center)
            {}

            TransformComponent(const TransformComponent& other) = default;
            TransformComponent(TransformComponent&& other) = default;

            /**
             * @brief Move the transformcomponent by a designated distance.
             * 
             * @param pos A vector2 representing amount by which position should be translated
             */
            void translate(const Vector2& pos);
            /**
             * @brief Move the transformcomponent by a designated distance.
             * 
             * @param x float representing the horizontal amount by which position should be translated
             * @param y float representing the vertical amount by which position should be translated
             */
            void translate(float x, float y);

            /**
             * @brief Set the position of the transformcomponent to a new one.
             * 
             * @param pos A Vector2 holding the new position
             */
            void setPosition(const Vector2& pos);
            /**
             * @brief Set the position of the transformcomponent to a new one.
             * 
             * @param x Float holding the x coordinate of the new position
             * @param y Float holding the y coordinate of the new position
             */
            void setPosition(float x, float y);
            /**
             * @brief Set the position of the transformcomponent to a new one.
             * 
             * @param pos A Vector2 holding the new position
             */
            void setLocalPosition(const Vector2& pos);
            /**
             * @brief Set the position of the transformcomponent to a new one.
             * 
             * @param x Float holding the x coordinate of the new position
             * @param y Float holding the y coordinate of the new position
             */
            void setLocalPosition(float x, float y);
            /**
             * @brief Returns the current position of this transformcomponent.
             * 
             * @return const Vector2& The position
             */
            const Vector2& getPosition() const;
            /**
             * @brief Returns the current center of this transformcomponent.
             * 
             * @return const Vector2& The center
             */
            const Vector2& getPositionCentered() const;
            /**
             * @brief Returns the current position of this transformcomponent.
             * 
             * @return const Vector2& The position
             */
            const Vector2& getLocalPosition() const;
            
            /**
             * @brief Set the scale of this transformcomponent.
             * 
             * @param scale A Vector2 representing the new scale of this transformcomponent
             */
            void setScale(const Vector2& scale);
            /**
             * @brief Set the scale of this transformcomponent.
             * 
             * @param x Float representing the horizontal scale of this transformcomponent
             * @param y Float representing the vertical scale of this transformcomponent
             */
            void setScale(float x, float y);
            /**
             * @brief Returns the current scale of this transformcomponent.
             * 
             * @return const Vector2& Vector2 representing the scale
             */
            const Vector2& getScale() const;

            void attachChild(std::shared_ptr<TransformComponent> child);

            std::string toString();
    };
}