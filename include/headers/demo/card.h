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
            std::shared_ptr<Sprite> _backSprite = nullptr;
            std::shared_ptr<Sprite> _hoverSprite = nullptr;
            std::shared_ptr<Sprite> _faceSprite = nullptr;

            std::shared_ptr<AudioAsset> _sfx = nullptr;
            std::shared_ptr<AudioAsset> _flipSfx = nullptr;
            std::shared_ptr<AudioAsset> _selectSfx = nullptr;

            bool m_flipped = false;
            bool m_isBomb = false;
            uint16_t value;
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
                
            }

            void start(Stage& stage) override
            {
                if (_backSprite) this->addComponent<SpriteRendererComponent>(SpriteRendererComponent(*this, _backSprite));
                
                this->addComponent<ColliderComponent>(ColliderComponent(*this, *this->getComponent<TransformComponent>(), "card"));
                _flipSfx = Loader::getAsset<AudioAsset>("sfxClick");
                _selectSfx = Loader::getAsset<AudioAsset>("sfxSelect");


                setupButton(this->getComponent<ColliderComponent>(), this->getComponent<SpriteRendererComponent>(), nullptr);

                Actor::start(stage);
            }

            void setCard(std::shared_ptr<Sprite> faceSprite, std::shared_ptr<Sprite> backSprite, std::shared_ptr<Sprite> hoverSprite, std::shared_ptr<AudioAsset> sfx, int val)
            {
                _faceSprite = faceSprite;
                _backSprite = backSprite;
                _hoverSprite = hoverSprite;

                _sfx = sfx;

                value = val;
                m_isBomb = (val == 4);
            }

            void reveal()
            {
                if (m_flipped) return;
                
                m_flipped = true;
                _spriteRenderer->setSprite(_faceSprite);
            }

            uint16_t getValue()
            {
                return value;
            }

            void update(double dt, Stage& stage) override
            {
                //
            } 

            /**
             * @brief We flip the card when it's clicked
             * 
             */
            void onClick() override
            {
                if (!m_flipped)
                {
                    reveal();
                    _stage->getAudioMixer()->playSound(_sfx);
                    if (m_isBomb) _stage->sendMessage("gameOver");
                    else
                    {
                        _stage->sendMessage(std::to_string(value));
                    }
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