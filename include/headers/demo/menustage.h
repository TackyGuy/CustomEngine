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
            std::shared_ptr<Actor> voltorbText = nullptr;
            std::shared_ptr<Button> sandboxButton = nullptr;
            std::shared_ptr<Actor> sandboxText = nullptr;

            SDL_Color colorText = {255, 255, 255};
        public:
            ~MenuStage(){}

            MenuStage(StageManager *stageManager, std::shared_ptr<AudioMixer> mixer) : Stage(stageManager, 32, 23, 32, mixer){}

            void preload() override
            {
                Loader::loadAsset("fontRegular", new FontAsset("res/fonts/weiholmir_regular.ttf", 14));
            }

            void start() override
            {
                auto font = Loader::getAsset<FontAsset>("fontRegular");
                Vector2 fontSize = Vector2(16, 16);
                float posX = 12;
                double textOffset = 1;

                voltorbButton = ActorManager::createActor<Button>(*this, center() + Vector2(posX, 4 * tileSize), Vector2(156, 56));
                voltorbButton->addComponent<ColliderComponent>(ColliderComponent(*voltorbButton, *voltorbButton->getComponent<TransformComponent>(), "ui", true));
                voltorbButton->setupButton(voltorbButton->getComponent<ColliderComponent>(), voltorbButton->getComponent<SpriteRendererComponent>(), nullptr);

                voltorbButton->OnClickBegin = ([&_stageManager = _stageManager](int type)
                {
                    if (type == 0)
                    {
                        if (_stageManager) _stageManager->setStage("voltorb");
                    }
                });
                voltorbText = ActorManager::createActor<Actor>(*this, center() + Vector2(posX, (4  + textOffset)* tileSize), fontSize);
                voltorbText->addComponent<TextComponent>(TextComponent(*voltorbText, "> Voltorb Flip", colorText, font));
                voltorbButton->attachChild(voltorbText);

                sandboxButton = ActorManager::createActor<Button>(*this, center() + Vector2(posX, 10 * tileSize), Vector2(156, 56));
                sandboxButton->addComponent<ColliderComponent>(ColliderComponent(*sandboxButton, *sandboxButton->getComponent<TransformComponent>(), "ui", true));
                sandboxButton->setupButton(sandboxButton->getComponent<ColliderComponent>(), sandboxButton->getComponent<SpriteRendererComponent>(), nullptr);

                sandboxButton->OnClickBegin = ([&_stageManager = _stageManager](int type)
                {
                    if (type == 0) 
                    {
                        if (_stageManager) _stageManager->setStage("sandbox");
                    }
                });
                sandboxText = ActorManager::createActor<Actor>(*this, center() + Vector2(posX, (10 + textOffset) * tileSize), fontSize);
                sandboxText->addComponent<TextComponent>(TextComponent(*sandboxText, "> Sandbox", colorText, font));
                sandboxButton->attachChild(sandboxText);

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