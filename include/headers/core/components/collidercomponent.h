#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include "SDL.h"

#include "basecomponent.h"
#include "transformcomponent.h"
#include "boundingbox.h"

namespace Core
{
    class ColliderComponent : public BaseComponent
    {
        private:
            BoundingBox *m_aabb = nullptr;
            std::vector<ColliderComponent*> _colliders;
            std::string m_tag;
            
            TransformComponent *_transform = nullptr;
            bool m_isTrigger = false;
            bool m_dirtyFlag = false;
        public:
            static const size_t Type;
            const size_t getType() const override
            {
                return Type;
            }

            ~ColliderComponent(){};
            // Pointer to a transform component
            // SDL_Rect
            // Tag of the collider
            ColliderComponent(BroadcasterInterface *broadcaster, TransformComponent *transform, Vector2 vec2, const std::string& str = "", bool isTrigger = false) : BaseComponent(broadcaster), _transform(transform), m_tag(str), m_isTrigger(isTrigger)
            {
                m_aabb = new BoundingBox(transform->getPosition(), vec2);
            }
            // Pointer to a transform component
            // Tag of the collider
            ColliderComponent(BroadcasterInterface *broadcaster, TransformComponent *transform, const std::string& str = "", bool isTrigger = false) : BaseComponent(broadcaster), _transform(transform), m_tag(str), m_isTrigger(isTrigger)
            {
                Vector2 extents(0, 0);
                extents.add(transform->getScale());
                extents.multiply(0.5f);
                m_aabb = new BoundingBox(transform->getPositionCentered(), extents);
            }

            BoundingBox *getAABB();
            bool isDirty() const;
            void setDirty(bool val);
            const std::string& getTag() const;
    };
}