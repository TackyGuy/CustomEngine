#pragma once

#include "SDL.h"

#include "stage.h"
#include "button.h"

using namespace Core;
namespace Menu
{
    class MenuStage: public Stage
    {
        private:
            std::shared_ptr<Button> voltorbButton = nullptr;
            std::shared_ptr<Button> sandboxButton = nullptr;
        public:
            ~MenuStage(){}

            MenuStage(StageManager *stageManager, std::shared_ptr<AudioMixer> mixer) : Stage(stageManager, 32, 23, 32, mixer){}

            void preload() override
            {
                Loader::loadAsset("uisheet", new SpritesheetAsset("res/sprites/user_interface/buttons.png", 16, 16));
            }

            void start() override
            {
                auto sprite = Loader::getAsset<SpritesheetAsset>("uisheet")->getSpriteAt(0);

                voltorbButton = ActorManager::createActor<Button>(*this, center() + Vector2(12.5 * tileSize, 6 * tileSize), Vector2(156, 56)); 
                voltorbButton->addComponent<SpriteRendererComponent>(SpriteRendererComponent(*voltorbButton, sprite));
                voltorbButton->addComponent<ColliderComponent>(ColliderComponent(*voltorbButton, *voltorbButton->getComponent<TransformComponent>(), "ui", true));
                voltorbButton->setupButton(voltorbButton->getComponent<ColliderComponent>(), voltorbButton->getComponent<SpriteRendererComponent>(), nullptr);

                voltorbButton->OnClickBegin = ([&_stageManager = _stageManager](int type)
                {
                    if (type == 0)
                    {
                        if (_stageManager) _stageManager->setStage("voltorb");
                    }
                });

                sandboxButton = ActorManager::createActor<Button>(*this, center() + Vector2(12.5 * tileSize, 12 * tileSize), Vector2(156, 56)); 
                sandboxButton->addComponent<SpriteRendererComponent>(SpriteRendererComponent(*sandboxButton, sprite));
                sandboxButton->addComponent<ColliderComponent>(ColliderComponent(*sandboxButton, *sandboxButton->getComponent<TransformComponent>(), "ui", true));
                sandboxButton->setupButton(sandboxButton->getComponent<ColliderComponent>(), sandboxButton->getComponent<SpriteRendererComponent>(), nullptr);

                sandboxButton->OnClickBegin = ([&_stageManager = _stageManager](int type)
                {
                    if (type == 0) 
                    {
                        if (_stageManager) _stageManager->setStage("sandbox");
                    }
                });

                Stage::start();
            }

            void update(double dt) override
            {

                Stage::update(dt);
            }

            /**
             * @brief Sends a message to the stage
             * 
             * @param msg The message as a string
             */
            virtual void sendMessage(std::string msg)
            {

            }
    };
}