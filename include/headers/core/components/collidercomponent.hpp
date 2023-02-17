#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include "SDL.h"

#include "basecomponent.hpp"
#include "transformcomponent.hpp"
#include "boundingbox.hpp"

namespace Core
{
    class ColliderComponent : public BaseComponent
    {
        private:
            std::string m_tag;
            
            bool m_isTrigger = false;
            bool m_dirtyFlag = false;
            
            BoundingBox m_aabb;
        public:
            static const size_t Type;
            const size_t getType() const override
            {
                return Type;
            }

            ~ColliderComponent(){}
            /**
             * @brief Construct a new Collider Component object and its BoundingBox.
             * 
             * @param actor The actor that implements the actor interface
             * @param center The center point of the BoundingBox of this collider
             * @param extents The extents (wingspan) of the BoundingBox of this collider
             * @param str The tag of this collider
             * @param isTrigger Is this collider trigger only?
             */
            ColliderComponent(const ActorInterface& actor, Vector2 center, Vector2 extents, const std::string& str = "", bool isTrigger = false) 
            : BaseComponent(actor), m_tag(str), m_isTrigger(isTrigger), m_aabb(center, extents)
            {}
            /**
             * @brief Construct a new Collider Component object and its BoundingBox.
             * 
             * @param actor The actor that implements the actor interface
             * @param p_transform The TransformComponent to reference
             * @param extents The extents (wingspan) of the BoundingBox of this collider
             * @param str The tag of this collider
             * @param isTrigger Is this collider trigger only?
             */
            ColliderComponent(const ActorInterface& actor, TransformComponent& p_transform, Vector2 extents, const std::string& str = "", bool isTrigger = false) 
            : BaseComponent(actor), m_tag(str), m_isTrigger(isTrigger), m_aabb(p_transform.getPosition(), extents)
            {}
            /**
             * @brief Construct a new Collider Component object and its BoundingBox.
             * 
             * @param actor The actor that implements the actor interface
             * @param p_transform The TransformComponent to reference
             * @param str The tag of this collider
             * @param isTrigger Is this collider trigger only?
             */
            ColliderComponent(const ActorInterface& actor, TransformComponent& p_transform, const std::string& str = "", bool isTrigger = false) 
            : BaseComponent(actor), m_tag(str), m_isTrigger(isTrigger)
            {
                Vector2 extents(0, 0);
                extents.add(p_transform.getScale());
                extents.multiply(0.5f);
                m_aabb = BoundingBox(p_transform.getPositionCentered(), extents);
            }

            ColliderComponent(ColliderComponent& other) = default;
            ColliderComponent(ColliderComponent&& other) = default;

            /**
             * @brief Returns a reference to the BoundingBox of this collider.
             * 
             * @return BoundingBox& The BoundingBox
             */
            BoundingBox& getAABB();
            /**
             * @brief Check if this collider is dirty.
             * 
             * @return true if dirty
             * @return false if not dirty
             */
            bool isDirty() const;
            /**
             * @brief Set the state of the dirty flag of this collider.
             * 
             * @param val The new value m_dirtyFlag should have
             */
            void setDirty(bool val);
            /**
             * @brief Return the tag of this collider.
             * 
             * @return const std::string& The tag
             */
            const std::string& getTag() const;
    };
}