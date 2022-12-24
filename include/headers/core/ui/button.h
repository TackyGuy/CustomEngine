#pragma once

#include <string>
#include <iostream>

#include "actor.h"
#include "userinterface.h"
#include "textcomponent.h"
#include "spriterenderercomponent.h"
#include "mathutils.h"

namespace Core
{
    class Button : public Actor, public UserInterface
    {
        private:
            int16_t uiID;
        protected:
            std::shared_ptr<ColliderComponent> _collider = nullptr;
            std::shared_ptr<SpriteRendererComponent> _spriteRenderer = nullptr;
            std::shared_ptr<TextComponent> _textRenderer = nullptr;
        
        public:
            int test = 0;
            ~Button()
            {
                UIManager::removeElement(uiID);
            }
            /**
             * @brief Construct a new Button object
             * 
             * @param pos The position of the button
             * @param scale The scale of the button
             * @param id The id of the button
             */
            Button(Stage &r_stage, const int id, const Vector2& pos, const Vector2& scale): Actor(r_stage, id, pos, scale)
            {
                
            }

            void init() override
            {
                Actor::init();
                
                uiID = UIManager::addElement(this);
            }

            /**
             * @brief Initializes the button by assigning the correct components
             * 
             * @param collider The ColliderComponent of the button if applicable
             * @param srComponent The SpriteRendererComponent of the button if applicable
             * @param txtRenderer The TextComponent of the button if applicable
             */
            virtual void setupButton(std::shared_ptr<ColliderComponent> collider, std::shared_ptr<SpriteRendererComponent> srComponent, std::shared_ptr<TextComponent> txtRenderer)
            {
                if (collider != nullptr) _collider = collider;

                if (srComponent != nullptr)
                {
                    _spriteRenderer = srComponent;
                }

                if (txtRenderer != nullptr)
                {
                    _textRenderer = txtRenderer;
                }
            }

            /**
             * @brief The behaviour of the button when clicked upon
             * 
             */
            virtual void onClick() override
            {
                std::cout << "button clicked!" << std::endl;
            }
            /**
             * @brief The behaviour of the button when the hover starts
             * 
             */
            virtual void onHoverBegin() override
            {
                std::cout << "button hover begin!" << std::endl;
            }
            /**
             * @brief The behaviour of the button when hovered on
             * 
             */
            virtual void onHover() override
            {
                std::cout << "button hover!" << std::endl;
            }
            /**
             * @brief The behaviour of the button when it stops being hovered
             * 
             */
            virtual void onHoverEnd() override
            {
                std::cout << "button hover end!" << std::endl;
            }

            /**
             * @brief Get the Collider object associated with this button
             * 
             * @return ColliderComponent* 
             */
            virtual std::shared_ptr<ColliderComponent>  getCollider() override
            {
                return _collider;
            }
    };
}