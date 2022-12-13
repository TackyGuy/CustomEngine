#pragma once


#include "button.h"
#include "loader.h"

using namespace Core;
namespace Demo1
{
    class Card: public Button
    {
        private:
            Sprite *_backSprite = nullptr;
            Sprite *_hoverSprite = nullptr;
            Sprite *_faceSprite = nullptr;

            bool m_flipped = false;
        public:
            ~Card(){}
            /**
             * @brief Construct a new Button object
             * 
             * @param pos The position of the button
             * @param scale The scale of the button
             * @param id The id of the button
             */
            Card(const Vector2& pos, const Vector2& scale, const int id): Button(pos, scale, id)
            {
                UIManager::s_uiElements.emplace_back(this);
            }

            void start(Stage& stage) override
            {
                _backSprite = Loader::getAsset<SpritesheetAsset>("spritesheet")->getSpriteAt(6).get();
                _hoverSprite = Loader::getAsset<SpritesheetAsset>("spritesheet")->getSpriteAt(5).get();
                this->addComponent<SpriteRendererComponent>(SpriteRendererComponent(this, _backSprite));
                
                this->addComponent<ColliderComponent>(ColliderComponent(this, this->getComponent<TransformComponent>(), "card"));


                setupButton(this->getComponent<ColliderComponent>(), this->getComponent<SpriteRendererComponent>(), nullptr);
            }

            void setFaceSprite(Sprite *sprite)
            {
                _faceSprite = sprite;
            }

            /**
             * @brief We flip the card when it's clicked
             * 
             */
            void onClick() override
            {
                m_flipped = true;
                _spriteRenderer->setSprite(_faceSprite);
            }
            /**
             * @brief We change the sprite of the card when hovered
             * 
             */
            void onHoverBegin() override
            {
                if (!m_flipped) _spriteRenderer->setSprite(_hoverSprite);
            }
            void onHover() override {}
            /**
             * @brief We change the sprite of the card when the hover event ends
             * 
             */
            void onHoverEnd() override
            {
               if (!m_flipped) _spriteRenderer->setSprite(_backSprite);
            }

    };
}