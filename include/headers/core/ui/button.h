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
        private:
            ColliderComponent *_collider;
            SpriteRendererComponent *_spriteRenderer;
            TextComponent *_textRenderer;
        
        public:
            ~Button(){}
            Button(const Vector2& pos, const Vector2& scale, const int id): Actor(pos, scale, id)
            {
                UIManager::s_uiElements.emplace_back(this);
            }

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

            virtual void onClick() override
            {
                std::cout << "button clicked!" << std::endl;
            }

            virtual ColliderComponent *getCollider() override
            {
                return _collider;
            }
    };
}