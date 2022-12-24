#pragma once

#include <iostream>
#include <map>

#include "mathutils.h"
#include "collision.h"
#include "boundingbox.h"

namespace Core
{
    class UserInterface
    {
        public:
            virtual ~UserInterface(){};
            /**
             * @brief How the UI element should act upon being clicked on
             * 
             */
            virtual void onClick() = 0;
            /**
             * @brief How the UI element should act when the hover starts
             * 
             */
            virtual void onHoverBegin() = 0;
            /**
             * @brief How the UI element should act while being hovered
             * 
             */
            virtual void onHover() = 0;
            /**
             * @brief How the UI element should act when the hover ends
             * 
             */
            virtual void onHoverEnd() = 0;
            /**
             * @brief Get the ColliderComponent object attached to the UI element.
             * 
             * @return ColliderComponent* a pointer to the ColliderComponent
             */
            virtual std::shared_ptr<ColliderComponent> getCollider() = 0;

            
    };
    class UIManager
    {
        private:
            ~UIManager(){};
            UIManager(){};
        public:
            inline static std::map<uint16_t, UserInterface*> s_uiElements;

            inline static int16_t addElement(UserInterface *uiElement)
            {   
                int16_t index = s_uiElements.size();
                s_uiElements.emplace(index, uiElement);

                return index;
            }
            inline static void removeElement(uint16_t index)
            {
                s_uiElements.erase(index);
            }

            inline static UserInterface *checkOverlapWithUI(const BoundingBox& mouseBox)
            {
                for (auto pair : s_uiElements)
                {
                    auto element = pair.second;

                    auto col = element->getCollider();
                    if (!col) continue;

                    if (Collision::AABB(mouseBox, col->getAABB())) 
                    {
                        return element;
                    }
                }

                return nullptr;
            }
    };
}