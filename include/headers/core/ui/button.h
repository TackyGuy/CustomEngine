#pragma once

#include <string>
#include <iostream>

#include "actor.h"
#include "userinterface.h"
#include "textcomponent.h"
#include "spriterenderercomponent.h"
#include "../math.h"

namespace Core
{
    class Button : public Actor, public UserInterface
    {
        protected:
            ColliderComponent *_collider;
            SpriteRendererComponent *_spriteRenderer;
            TextComponent *_textRenderer;
        
        public:
            ~Button(){}
            /**
             * @brief Construct a new Button object
             * 
             * @param pos The position of the button
             * @param scale The scale of the button
             * @param id The id of the button
             */
            Button(const Vector2& pos, const Vector2& scale, const int id): Actor(pos, scale, id)
            {
                UIManager::s_uiElements.emplace_back(this);
            }

            /**
             * @brief Initializes the button by assigning the correct components
             * 
             * @param collider The ColliderComponent of the button if applicable
             * @param srComponent The SpriteRendererComponent of the button if applicable
             * @param txtRenderer The TextComponent of the button if applicable
             */
            virtual void setupButton(ColliderComponent *collider, SpriteRendererComponent *srComponent, TextComponent *txtRenderer)
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
            virtual ColliderComponent *getCollider() override
            {
                return _collider;
            }
    };
}