#pragma once

#include <iostream>
#include <vector>

#include "math.h"
#include "collision.h"
#include "boundingbox.h"

namespace Core
{
    class UserInterface
    {
        public:

            /**
             * @brief How the UI element should act upon being clicked on
             * 
             */
            virtual void onClick() = 0;
            /**
             * @brief Get the ColliderComponent object attached to the UI element.
             * 
             * @return ColliderComponent* a pointer to the ColliderComponent
             */
            virtual ColliderComponent *getCollider() = 0;
    };
    class UIManager
    {
        private:
            ~UIManager(){};
            UIManager(){};
        public:
            inline static std::vector<UserInterface*> s_uiElements;

            inline static UserInterface *checkOverlapWithUI(BoundingBox *mouseBox)
            {
                if (mouseBox == nullptr) return nullptr;
                // std::vector<Actor*> contacts;

                for (auto element : s_uiElements)
                {
                    ColliderComponent *col = element->getCollider();

                    if (col == nullptr) continue;
                    if (col->getAABB() == nullptr) continue;

                    if (Collision::AABB(mouseBox, col->getAABB())) 
                    {
                        return element;
                    }
                }

                return nullptr;
            }
    };
}