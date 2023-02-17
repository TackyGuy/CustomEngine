#pragma once

#include "basecomponent.hpp"
#include "transformcomponent.hpp"
#include "collidercomponent.hpp"
#include "boundingbox.hpp"
#include "collision.hpp"
#include "mathutils.hpp"

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
            static const size_t Type;
            const size_t getType() const override
            {
                return Type;
            }
            enum Body
            {
                STATIC,
                DYNAMIC
            };
            Body bodyType;

            ~RigidbodyComponent(){}
            /**
             * @brief Construct a new RigidbodyComponent object
             * 
             * @param actor The actor that implements the IBroadcaster interface
             * @param transform The TransformComponent
             * @param collider The ColliderComponent
             * @param type The type of RigidBody this RigidbodyComponent should be
             */
            RigidbodyComponent(const ActorInterface& actor, std::shared_ptr<TransformComponent> transform, std::shared_ptr<ColliderComponent> collider, Body type) : 
            BaseComponent(actor), _transform(transform), _collider(collider), bodyType(type)
            {
                if (!Collision::findCollider(actorInterface.getID())) Collision::addCollider(actorInterface.getID(), _collider);
            }

            RigidbodyComponent(RigidbodyComponent& other) = default;
            RigidbodyComponent(RigidbodyComponent&& other):
                BaseComponent(other.actorInterface)
            {
                _transform = other._transform;
                _collider = other._collider;
                bodyType = other.bodyType;

                other._transform = nullptr;
                other._collider = nullptr;
            }

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