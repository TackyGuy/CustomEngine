#pragma once

#include "button.h"
#include "loader.h"
#include "audioasset.h"

using namespace Core;
namespace Demo1
{
    class Card: public Button
    {
        private:
            Sprite *_backSprite = nullptr;
            Sprite *_hoverSprite = nullptr;
            Sprite *_faceSprite = nullptr;

            AudioAsset *_sfx = nullptr;
            AudioAsset *_flipSfx = nullptr;
            AudioAsset *_selectSfx = nullptr;

            bool m_flipped = false;
            bool m_isBomb = false;
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
                if (_backSprite) this->addComponent<SpriteRendererComponent>(SpriteRendererComponent(this, _backSprite));
                
                this->addComponent<ColliderComponent>(ColliderComponent(this, this->getComponent<TransformComponent>(), "card"));
                _flipSfx = Loader::getAsset<AudioAsset>("sfxClick");
                _selectSfx = Loader::getAsset<AudioAsset>("sfxSelect");


                setupButton(this->getComponent<ColliderComponent>(), this->getComponent<SpriteRendererComponent>(), nullptr);

                Actor::start(stage);
            }

            void setCard(Sprite *faceSprite, Sprite *backSprite, Sprite *hoverSprite, AudioAsset *sfx, bool isBomb = false)
            {
                _faceSprite = faceSprite;
                _backSprite = backSprite;
                _hoverSprite = hoverSprite;

                _sfx = sfx;

                m_isBomb = isBomb;
            }

            void update(double dt, Stage& stage) override
            {
                if (m_flipped && m_isBomb) stage.sendMessage("gameOver");
            } 

            /**
             * @brief We flip the card when it's clicked
             * 
             */
            void onClick() override
            {
                if (!m_flipped)
                {
                    m_flipped = true;
                    _spriteRenderer->setSprite(_faceSprite);
                    _stage->getAudioMixer()->playSound(_sfx);
                }
            }
            /**
             * @brief We change the sprite of the card when hovered
             * 
             */
            void onHoverBegin() override
            {
                if (!m_flipped) 
                {
                    _spriteRenderer->setSprite(_hoverSprite);
                    _stage->getAudioMixer()->playSound(_selectSfx);
                }
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