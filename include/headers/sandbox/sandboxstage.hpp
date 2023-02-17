#pragma once

#include <random>

#include "stage.hpp"
#include "hero.hpp"
#include "button.hpp"
#include "basecomponent.hpp"
#include "transformcomponent.hpp"
#include "spriterenderercomponent.hpp"
#include "collidercomponent.hpp"
#include "textcomponent.hpp"


using namespace Core;

namespace Sandbox
{
    class SandboxStage: public Stage
    {
        private:
            bool gameOver = false;
            std::shared_ptr<Actor> _counter= nullptr;
            std::vector<Actor*> tiles;
            std::shared_ptr<Actor> backgroundProp = nullptr;
        public: 
            ~SandboxStage(){}
            SandboxStage(StageManager *stageManager, std::shared_ptr<AudioMixer> mixer) : Stage(stageManager, 32, 23, 32, mixer){}

            void preload() override
            {
                Loader::loadAsset("hero", new SpritesheetAsset("res/sprites/characters/hero.png", 48, 48));
                Loader::loadAsset("tileset", new SpritesheetAsset("res/sprites/tiles_dungeon.png", 16, 16));
                Loader::loadAsset("icons", new SpritesheetAsset("res/sprites/user_interface/icons.png", 16, 16));

                Loader::loadAsset("weiholmirRegular", new FontAsset("res/fonts/weiholmir_regular.ttf", 16));
                Loader::loadAsset("music", new AudioAsset("res/sounds/pokeMart.mp3", true));
            }

            void start() override
            {
                std::cout << "initializing test stage" << std::endl;

                std::shared_ptr<Sprite> backgroundTile = Loader::getAsset<SpritesheetAsset>("tileset")->getSpriteAt(3);
                backgroundProp = ActorManager::createActor<Actor>(*this, Vector2(0, 0), Vector2(stageWidth * tileSize, stageHeight * tileSize));
                backgroundProp->addComponent<SpriteRendererComponent>(SpriteRendererComponent(*backgroundProp, backgroundTile));
                const int numTiles = 16;
                std::shared_ptr<Sprite> groundTiles[numTiles] = 
                {
                    Loader::getAsset<SpritesheetAsset>("tileset")->getSpriteAt(80),
                    Loader::getAsset<SpritesheetAsset>("tileset")->getSpriteAt(80),
                    Loader::getAsset<SpritesheetAsset>("tileset")->getSpriteAt(80),
                    Loader::getAsset<SpritesheetAsset>("tileset")->getSpriteAt(80),
                    Loader::getAsset<SpritesheetAsset>("tileset")->getSpriteAt(80),
                    Loader::getAsset<SpritesheetAsset>("tileset")->getSpriteAt(80),
                    Loader::getAsset<SpritesheetAsset>("tileset")->getSpriteAt(80),
                    Loader::getAsset<SpritesheetAsset>("tileset")->getSpriteAt(80),
                    Loader::getAsset<SpritesheetAsset>("tileset")->getSpriteAt(80),
                    Loader::getAsset<SpritesheetAsset>("tileset")->getSpriteAt(80),
                    Loader::getAsset<SpritesheetAsset>("tileset")->getSpriteAt(405),
                    Loader::getAsset<SpritesheetAsset>("tileset")->getSpriteAt(406),
                    Loader::getAsset<SpritesheetAsset>("tileset")->getSpriteAt(407),
                    Loader::getAsset<SpritesheetAsset>("tileset")->getSpriteAt(425),
                    Loader::getAsset<SpritesheetAsset>("tileset")->getSpriteAt(426),
                    Loader::getAsset<SpritesheetAsset>("tileset")->getSpriteAt(427)
                };

                std::shared_ptr<Sprite> wallTiles[2] =
                {
                    Loader::getAsset<SpritesheetAsset>("tileset")->getSpriteAt(440),
                    Loader::getAsset<SpritesheetAsset>("tileset")->getSpriteAt(444)
                };

                std::random_device rd;
                std::default_random_engine randEng(rd());
                std::uniform_int_distribution<int> distrWall(0, (2 - 1));
                std::uniform_int_distribution<int> distrGround(0, (numTiles - 1));

                int minX = 3;
                int maxX = (stageWidth - 4);
                int minY = 2;
                int maxY = (stageHeight - 3);

                for (auto x = 0; x < stageWidth; x++)
                {
                    for (auto y = 0; y < stageHeight; y++)
                    {
                        auto newTile = ActorManager::createActor<Actor>(*this, Vector2(x * tileSize, y * tileSize), Vector2(tileSize, tileSize));
                        std::shared_ptr<Sprite> tileSpr = nullptr;

                        if (x >= minX && x <= maxX) 
                        {
                            if (y >= minY && y <= maxY)
                            {
                                if (x == minX || x == maxX) 
                                {
                                    if (x == minX && y == minY) tileSpr = Loader::getAsset<SpritesheetAsset>("tileset")->getSpriteAt(428);
                                    else if (x == maxX && y == minY) tileSpr = Loader::getAsset<SpritesheetAsset>("tileset")->getSpriteAt(429);
                                    else if (x == minX && y == maxY) tileSpr = Loader::getAsset<SpritesheetAsset>("tileset")->getSpriteAt(448);
                                    else if (x == maxX && y == maxY) tileSpr = Loader::getAsset<SpritesheetAsset>("tileset")->getSpriteAt(449);
                                    else tileSpr = wallTiles[distrWall(randEng)];
                                }
                                else if (y == minY)
                                {
                                    tileSpr = Loader::getAsset<SpritesheetAsset>("tileset")->getSpriteAt(402);
                                }
                                else if (y == maxY)
                                {
                                    tileSpr = Loader::getAsset<SpritesheetAsset>("tileset")->getSpriteAt(431);
                                }
                                else tileSpr = groundTiles[distrGround(randEng)];
                            }
                        }

                        if (tileSpr != nullptr) newTile->addComponent<SpriteRendererComponent>(SpriteRendererComponent(*newTile, tileSpr));
                    }
                }

                auto leftWall = ActorManager::createActor<Actor>(*this, Vector2((minX - 1) * tileSize, minY * tileSize), Vector2(1, 1));
                leftWall->addComponent<ColliderComponent>(ColliderComponent(*leftWall, *leftWall->getComponent<TransformComponent>(), Vector2(10, 500), "wall_left"));
                leftWall->addComponent<RigidbodyComponent>(RigidbodyComponent(*leftWall, leftWall->getComponent<TransformComponent>(), 
                    leftWall->getComponent<ColliderComponent>(), RigidbodyComponent::Body::STATIC));

                auto rightWall = ActorManager::createActor<Actor>(*this, Vector2((maxX - 2) * tileSize, minY * tileSize), Vector2(1, 1));
                rightWall->addComponent<ColliderComponent>(ColliderComponent(*rightWall, *rightWall->getComponent<TransformComponent>(), Vector2(10, 500), "wall_right"));
                rightWall->addComponent<RigidbodyComponent>(RigidbodyComponent(*rightWall, rightWall->getComponent<TransformComponent>(), 
                    rightWall->getComponent<ColliderComponent>(), RigidbodyComponent::Body::STATIC));

                auto topWall = ActorManager::createActor<Actor>(*this, Vector2((minX - 1) * tileSize, (minY - 2) * tileSize), Vector2(1, 1));
                topWall->addComponent<ColliderComponent>(ColliderComponent(*topWall, *topWall->getComponent<TransformComponent>(), Vector2(800, 10), "wall_top"));
                topWall->addComponent<RigidbodyComponent>(RigidbodyComponent(*topWall, topWall->getComponent<TransformComponent>(), 
                    topWall->getComponent<ColliderComponent>(), RigidbodyComponent::Body::STATIC));

                auto bottomWall = ActorManager::createActor<Actor>(*this, Vector2((minX - 1) * tileSize, (maxY - 2.25f) * tileSize), Vector2(1, 1));
                bottomWall->addComponent<ColliderComponent>(ColliderComponent(*bottomWall, *bottomWall->getComponent<TransformComponent>(), Vector2(800, 10), "wall_bottom"));
                bottomWall->addComponent<RigidbodyComponent>(RigidbodyComponent(*bottomWall, bottomWall->getComponent<TransformComponent>(), 
                    bottomWall->getComponent<ColliderComponent>(), RigidbodyComponent::Body::STATIC));
                

                std::shared_ptr<Hero> player = ActorManager::createActor<Hero>(*this, Vector2(250, 150), Vector2(128, 128));

                _counter = ActorManager::createActor<Actor>(*this, Vector2((center().getX() - 2) * tileSize, (minY - 1) * tileSize), Vector2(10, 10));
                SDL_Color colorWhite = {255, 255, 255};
                _counter->addComponent<TextComponent>(TextComponent(*_counter, "0", colorWhite, Loader::getAsset<FontAsset>("weiholmirRegular")));

                setUI();
                _audioMixer->setMusicVolume(3);
                _audioMixer->playMusic(Loader::getAsset<AudioAsset>("music"));

                Stage::start();
            }

            void setUI()
            {
                auto heartSprite = Loader::getAsset<SpritesheetAsset>("icons")->getSpriteAt(0);
                auto heart = ActorManager::createActor<Actor>(*this, Vector2(10, 10), Vector2(40, 40));
                heart->addComponent<SpriteRendererComponent>(SpriteRendererComponent(*heart, heartSprite));

                auto heart2 = ActorManager::createActor<Actor>(*this, Vector2(55, 10), Vector2(40, 40));
                heart2->addComponent<SpriteRendererComponent>(SpriteRendererComponent(*heart2, heartSprite));

                auto heart3 = ActorManager::createActor<Actor>(*this, Vector2(100, 10), Vector2(40, 40));
                heart3->addComponent<SpriteRendererComponent>(SpriteRendererComponent(*heart3, heartSprite));
            }

            void update(double dt) override
            {
                if (!gameOver)
                {
                    std::stringstream stream;
                    stream << "Elapsed: " << getTime();
                    std::string str = stream.str();
                    _counter->getComponent<TextComponent>()->setText(str);

                    if (_inputProvider->isKeyPressed(SDL_SCANCODE_ESCAPE)) _stageManager->setStage("menu");
                }

                Stage::update(dt);
            }

            void sendMessage(std::string msg) override
            {

            }
    };
}