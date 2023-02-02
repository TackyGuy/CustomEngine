#pragma once

#include "button.h"
#include "loader.h"
#include "actormanager.h"

using namespace Core;
namespace Demo1
{
    class MuteButton : public Button
    {
        private:
            bool m_soundsMuted = false;
            std::shared_ptr<Sprite> _spriteActive = nullptr;
            std::shared_ptr<Sprite> _spriteInactive = nullptr;

            std::shared_ptr<AudioMixer> _audioMixer = nullptr;
        public:
            ~MuteButton(){}

            MuteButton(Stage &r_stage, const int id, const Vector2& pos, const Vector2& scale, std::shared_ptr<Actor> parent = nullptr)
                : Button(r_stage, id, pos, scale, parent){}
            
            void start() override
            {
                _spriteActive = Loader::getAsset<SpritesheetAsset>("uisheet")->getSpriteAt(126);
                _spriteInactive = Loader::getAsset<SpritesheetAsset>("uisheet")->getSpriteAt(127);
                this->addComponent<SpriteRendererComponent>(SpriteRendererComponent(*this, _spriteActive));
                const auto transform = this->getComponent<TransformComponent>();
                this->addComponent<ColliderComponent>(ColliderComponent(*this, *transform, "ui", true));

                setupButton(this->getComponent<ColliderComponent>(), this->getComponent<SpriteRendererComponent>(), nullptr);

                Actor::start();
            }

            void setMixer(std::shared_ptr<AudioMixer> audioMixer)
            {
                _audioMixer = audioMixer;
            }

            /**
             * @brief We hide the Deductions
             * 
             */
            void onClickEnd(int type) override
            {
                m_soundsMuted = !m_soundsMuted;

                if (m_soundsMuted)
                {
                    this->getComponent<SpriteRendererComponent>()->setSprite(_spriteInactive);
                    if (_audioMixer) _audioMixer->togglePlay(false);
                }
                else
                {
                    this->getComponent<SpriteRendererComponent>()->setSprite(_spriteActive);
                    if (_audioMixer) _audioMixer->togglePlay(true);
                }
            }


    };
}