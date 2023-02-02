#pragma once

#include "button.h"
#include "loader.h"
#include "actormanager.h"
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

            std::shared_ptr<Actor> _voltorbDeduction = nullptr;
            std::shared_ptr<Actor> _oneDeduction = nullptr;
            std::shared_ptr<Actor> _twoDeduction = nullptr;
            std::shared_ptr<Actor> _threeDeduction = nullptr;

            std::shared_ptr<AudioAsset> _sfx = nullptr;
            std::shared_ptr<AudioAsset> _flipSfx = nullptr;
            std::shared_ptr<AudioAsset> _selectSfx = nullptr;

            bool m_flipped = false;
            bool m_isBomb = false;
            std::pair<int, int> m_cardIndex;
            uint16_t value;
        public:
            ~Card()
            {
                if (_voltorbDeduction) ActorManager::unregisterActor(*_voltorbDeduction);
                if (_oneDeduction) ActorManager::unregisterActor(*_oneDeduction);
                if (_twoDeduction) ActorManager::unregisterActor(*_twoDeduction);
                if (_threeDeduction) ActorManager::unregisterActor(*_threeDeduction);
            }
            /**
             * @brief Construct a new Button object
             * 
             * @param pos The position of the button
             * @param scale The scale of the button
             * @param id The id of the button
             */
            Card(Stage &r_stage, const int id, const Vector2& pos, const Vector2& scale, std::shared_ptr<Actor> parent = nullptr): Button(r_stage, id, pos, scale, parent)
            {
                //
            }

            void start() override
            {
                if (_backSprite) this->addComponent<SpriteRendererComponent>(SpriteRendererComponent{*this, _backSprite});
                
                this->addComponent<ColliderComponent>(ColliderComponent{*this, *this->getComponent<TransformComponent>(), "card", true});
                _flipSfx = Loader::getAsset<AudioAsset>("sfxClick");
                _selectSfx = Loader::getAsset<AudioAsset>("sfxSelect");


                setupButton(this->getComponent<ColliderComponent>(), this->getComponent<SpriteRendererComponent>(), nullptr);

                Actor::start();
            }

            void setCard(std::shared_ptr<Sprite> faceSprite, std::shared_ptr<Sprite> backSprite, std::shared_ptr<Sprite> hoverSprite, std::shared_ptr<AudioAsset> sfx, int val, int x, int y)
            {
                _faceSprite = faceSprite;
                _backSprite = backSprite;
                _hoverSprite = hoverSprite;

                _sfx = sfx;

                value = val;
                m_isBomb = (val == 4);

                m_cardIndex = std::make_pair(x, y);
            }

            void createDeductions(std::shared_ptr<Sprite> voltorbSpr, std::shared_ptr<Sprite> oneSpr, std::shared_ptr<Sprite> twoSpr, std::shared_ptr<Sprite> threeSpr)
            {
                Vector2 size = Vector2(25, 25);
                Vector2 pos = this->getComponent<TransformComponent>()->getPositionCentered() - Vector2(13, 13);

                float offset = 20.0f;
                _voltorbDeduction = ActorManager::createActor<Actor>(stage, pos + Vector2(-offset, -offset), size);
                _voltorbDeduction->addComponent<SpriteRendererComponent>(SpriteRendererComponent(*this, voltorbSpr));
                _voltorbDeduction->setActive(false);

                _oneDeduction = ActorManager::createActor<Actor>(stage, pos + Vector2(offset, -offset), size);
                _oneDeduction->addComponent<SpriteRendererComponent>(SpriteRendererComponent(*this, oneSpr));
                _oneDeduction->setActive(false);


                _twoDeduction = ActorManager::createActor<Actor>(stage, pos + Vector2(-offset, offset), size);
                _twoDeduction->addComponent<SpriteRendererComponent>(SpriteRendererComponent(*this, twoSpr));
                _twoDeduction->setActive(false);

                _threeDeduction = ActorManager::createActor<Actor>(stage, pos + Vector2(offset, offset), size);
                _threeDeduction->addComponent<SpriteRendererComponent>(SpriteRendererComponent(*this, threeSpr));
                _threeDeduction->setActive(false);

            }

            void reveal()
            {
                if (m_flipped) return;
                
                m_flipped = true;
                _spriteRenderer->setSprite(_faceSprite);
                _collider->setActive(false);
                hideDeductions();
            }

            void toggleDeduction(int index)
            {
                if (m_flipped) return;

                switch (index)
                {
                    case 3:
                        _threeDeduction->setActive(!_threeDeduction->isActive());
                        break;
                    case 2:
                        _twoDeduction->setActive(!_twoDeduction->isActive());
                        break;
                    case 1:
                        _oneDeduction->setActive(!_oneDeduction->isActive());
                        break;
                    default:
                        _voltorbDeduction->setActive(!_voltorbDeduction->isActive());
                        break;
                }
            }
            void hideDeductions()
            {
                _threeDeduction->setActive(false);
                _twoDeduction->setActive(false);
                _oneDeduction->setActive(false);
                _voltorbDeduction->setActive(false);
            }

            uint16_t getValue()
            {
                return value;
            }

            void update(double dt) override
            {
                
            } 

            /**
             * @brief We flip the card when it's clicked or show the Deductions
             * 
             */
            void onClick(int type) override
            {
                switch (type)
                {
                    case 2:
                        // 
                        break;

                    default:
                        if (!m_flipped)
                        {
                            reveal();
                            stage.getAudioMixer()->playSound(_sfx, stage.getTime());
                            if (m_isBomb) stage.sendMessage("gameOver");
                            else
                            {
                                stage.sendMessage(std::to_string(value));
                            }
                        }
                        break;
                }
            }
            /**
             * @brief We hide the Deductions
             * 
             */
            void onClickEnd(int type) override
            {

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
                    stage.getAudioMixer()->playSound(_selectSfx, stage.getTime());

                    std::string str = "select_";
                    str += std::to_string(m_cardIndex.first);
                    str += "_";
                    str += std::to_string(m_cardIndex.second);
                    stage.sendMessage(str);
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