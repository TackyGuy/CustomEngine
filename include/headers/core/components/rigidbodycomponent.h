#pragma once

#include "basecomponent.h"
#include "transformcomponent.h"
#include "collidercomponent.h"
#include "boundingbox.h"
#include "collision.h"
#include "math.h"

namespace Core
{
    class RigidbodyComponent : public BaseComponent
    {
        private:
            std::shared_ptr<TransformComponent> _transform = nullptr;
            std::shared_ptr<ColliderComponent> _collider = nullptr;
            Vector2 m_velocity = Vector2(0, 0);

            void resolveCollision();
        public:
            enum Body
            {
                STATIC,
                DYNAMIC
            };
            Body bodyType;
            static const size_t Type;
            const size_t getType() const override
            {
                return Type;
            }

            ~RigidbodyComponent(){}
            /**
             * @brief Construct a new RigidbodyComponent object
             * 
             * @param p_broadcaster The actor that implements the IBroadcaster interface
             * @param transform The TransformComponent
             * @param collider The ColliderComponent
             * @param type The type of RigidBody this RigidbodyComponent should be
             */
            RigidbodyComponent(const BroadcasterInterface& p_broadcaster, std::shared_ptr<TransformComponent> transform, std::shared_ptr<ColliderComponent> collider, Body type) : 
            BaseComponent(p_broadcaster), _transform(transform), _collider(collider), bodyType(type)
            {}

            virtual void update(double dt, Stage& stage) override
            {
                if (bodyType == Body::DYNAMIC)
                {
                    if (m_velocity.getX() == 0 && m_velocity.getY() == 0) return;

                    resolveCollision();
                }
            }

            virtual void onCollision(std::weak_ptr<ColliderComponent> other)
            {
                //
            }

            /**
             * @brief Set the velocity of this rigidbody.
             * 
             * @param vec2 
             */
            void setVelocity(Vector2& vec2);
            /**
             * @brief Returns the velocity of this rigidbody.
             * 
             * @return const Vector2& 
             */
            const Vector2& getVelocity() const;

            /**
             * @brief Returns the collider held by this rigidbody.
             * 
             * @return std::shared_ptr<ColliderComponent> 
             */
            std::shared_ptr<ColliderComponent> getCollider();
    };
}