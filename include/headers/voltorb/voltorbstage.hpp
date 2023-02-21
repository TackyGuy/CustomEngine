#pragma once

#include <vector>
#include <array>
#include <random>
#include "SDL.h"

#include "stage.hpp"
#include "card.hpp"
#include "mutebutton.hpp"

using namespace Core;
namespace VoltorbFlip
{
    class VoltorbStage: public Stage
    {
        private:
            bool m_gameOver = false;
            const double endDelay = 5;
            double m_timeOfDeath = -1;
            uint16_t m_currentScore;
            uint16_t m_requiredScore;
            // Represents the game table
            std::vector<std::shared_ptr<Actor>> _table;
            const int CARDS_PER_ROW = 5;
            const int CARDS_PER_COLUMN = 5;
            std::array<std::array<std::shared_ptr<Card>, 5>, 5> _cardsArray;
            std::shared_ptr<Card> _selectedCard = nullptr;
            std::shared_ptr<Actor> _deductionWheel = nullptr;
            std::shared_ptr<Actor> _textCurrentScore = nullptr;
            std::shared_ptr<Actor> _textShadow = nullptr;
            std::shared_ptr<MuteButton> _muteButton = nullptr;

            SDL_Color colorBlack = {0, 0, 0};
        public:
            ~VoltorbStage(){}

            VoltorbStage(StageManager *stageManager, std::shared_ptr<AudioMixer> mixer) : Stage(stageManager, 32, 23, 32, mixer){}

            void preload() override
            {
                Loader::loadAsset("spritesheet", new SpritesheetAsset("res/sprites/voltorb/spritesheet.png", 28, 28));
                Loader::loadAsset("uisheet", new SpritesheetAsset("res/sprites/user_interface/buttons.png", 16, 16));

                Loader::loadAsset("musicMain", new AudioAsset("res/sounds/gameCorner.mp3", true));
                Loader::loadAsset("musicEnd", new AudioAsset("res/sounds/pokeLullaby.mp3", true));
                Loader::loadAsset("sfxClick", new AudioAsset("res/sounds/click.wav", false));
                Loader::loadAsset("sfxSelect", new AudioAsset("res/sounds/select.wav", false));
                Loader::loadAsset("sfxCard1", new AudioAsset("res/sounds/card1.wav", false));
                Loader::loadAsset("sfxCard2", new AudioAsset("res/sounds/card2.wav", false));
                Loader::loadAsset("sfxCard3", new AudioAsset("res/sounds/card3.wav", false));
                Loader::loadAsset("sfxExplosion", new AudioAsset("res/sounds/explosion.wav", false));

                Loader::loadAsset("fontSmall", new FontAsset("res/fonts/weiholmir_regular.ttf", 12));
                Loader::loadAsset("fontRegular", new FontAsset("res/fonts/weiholmir_regular.ttf", 14));
                Loader::loadAsset("fontLarge", new FontAsset("res/fonts/weiholmir_regular.ttf", 18));
            }

            void start() override
            {
                std::cout << "Welcome to Voltorb Flip!" << std::endl;

                _audioMixer->setMusicVolume(2);
                _audioMixer->playMusic(Loader::getAsset<AudioAsset>("musicMain"));
                _audioMixer->setSoundVolume(1);

                m_currentScore = 1;

                createTable();
                
                Stage::start();
            }

            void createTable()
            {
                std::cout << "Create table..." << std::endl;
                auto backgroundProp = ActorManager::createActor<Actor>(*this, Vector2(0, 0), Vector2(stageWidth * tileSize, stageHeight * tileSize));
                backgroundProp->addComponent<SpriteRendererComponent>(SpriteRendererComponent(*backgroundProp, Loader::getAsset<SpritesheetAsset>("spritesheet")->getSpriteAt(0)));
                _table.emplace_back(backgroundProp);

                m_requiredScore = 1;
                placeCards();

                createUI();

                if (!_audioMixer->isPlaying()) _audioMixer->togglePlay();
            }

            void placeCards()
            {
                std::random_device rd;
                std::default_random_engine randEngine(rd());
                std::uniform_int_distribution<int> distrCardFaces(1, 4);

                int startX = 9 * tileSize;
                int startY = 3 * tileSize;
                int cardSize = 80;
                int margin = 10;

                std::shared_ptr<SpritesheetAsset> spritesheet = Loader::getAsset<SpritesheetAsset>("spritesheet");

                // Creates the cards and wires
                for (int x = 0; x < CARDS_PER_ROW; x++)
                {
                    for (int y = 0; y < CARDS_PER_COLUMN; y++)
                    {
                        Vector2 pos = Vector2(startX + x * (cardSize + margin), startY + y * (cardSize + margin));
                        // We create the visual wires here also
                        auto wireY = ActorManager::createActor<Actor>(*this, pos + Vector2(0, 19), Vector2(cardSize, cardSize));
                        wireY->addComponent<SpriteRendererComponent>(SpriteRendererComponent(*wireY, spritesheet->getSpriteAt(32 + x)));
                        _table.emplace_back(wireY);

                        auto wireX = ActorManager::createActor<Actor>(*this, pos + Vector2(19, 0), Vector2(cardSize, cardSize));
                        wireX->addComponent<SpriteRendererComponent>(SpriteRendererComponent(*wireX, spritesheet->getSpriteAt(37 + y)));
                        _table.emplace_back(wireX);

                        auto card = ActorManager::createActor<Card>(*this, pos, Vector2(cardSize, cardSize));

                        int cardIndex = distrCardFaces(randEngine);
                        if (cardIndex < 4) m_requiredScore *= cardIndex;

                        int spriteOffset = 1;
                        if (x == 0)
                        {
                            if (y > 0) spriteOffset += 5;
                        }
                        else
                        {
                            if (y == 0) spriteOffset += 10;
                            else spriteOffset += 15;
                        }

                        std::string sfxName = (cardIndex == 4)? "sfxExplosion" : "sfxCard" + std::to_string(cardIndex);
                        
                        card->setCard(
                            spritesheet->getSpriteAt(cardIndex + spriteOffset), 
                            spritesheet->getSpriteAt(spriteOffset), 
                            spritesheet->getSpriteAt(21),
                            Loader::getAsset<AudioAsset>(sfxName),
                            cardIndex,
                            x,
                            y
                            );
                        card->createDeductions(
                            spritesheet->getSpriteAt(44),
                            spritesheet->getSpriteAt(45),
                            spritesheet->getSpriteAt(46),
                            spritesheet->getSpriteAt(47)
                        );

                        _cardsArray[x].at(y) = card;
                        _table.emplace_back(card);
                    }
                }
                
                createHints(cardSize, margin, startX, startY);
            }

            void createHints(int cardSize, int margin, int startX, int startY)
            {
                for (int i = 0; i < CARDS_PER_ROW; i++)
                {
                    int totalNums = 0;
                    int totalVoltorbs = 0;
                    for (int j = 0; j < CARDS_PER_COLUMN; j++)
                    {
                        int cardValue = _cardsArray[i].at(j)->getValue();
                        if (cardValue == 4) totalVoltorbs++;
                        else totalNums += cardValue;
                    }

                    createHint(totalNums, totalVoltorbs, i + 27, Vector2(startX + i * (cardSize + margin), startY + CARDS_PER_COLUMN * (cardSize + margin)),Vector2(cardSize, cardSize));
                }

                for (int i = 0; i < CARDS_PER_COLUMN; i++)
                {
                    int totalNums = 0;
                    int totalVoltorbs = 0;
                    for (int j = 0; j < CARDS_PER_ROW; j++)
                    {
                        int cardValue = _cardsArray[j].at(i)->getValue();
                        if (cardValue == 4) totalVoltorbs++;
                        else totalNums += cardValue;
                    }

                    createHint(totalNums, totalVoltorbs, i + 22, Vector2(startX + CARDS_PER_ROW * (cardSize + margin), startY + i * (cardSize + margin)),Vector2(cardSize, cardSize));
                }
            }

            void createHint(int sumNumbers, int sumVoltorbs, int spriteIndex, Vector2 position, Vector2 size)
            {
                auto font = Loader::getAsset<FontAsset>("fontRegular");

                auto hintCard = ActorManager::createActor<Actor>(*this, position, size);
                hintCard->addComponent<SpriteRendererComponent>(SpriteRendererComponent(*hintCard, Loader::getAsset<SpritesheetAsset>("spritesheet")->getSpriteAt(spriteIndex)));
                _table.emplace_back(hintCard);

                auto hintTextNum = ActorManager::createActor<Actor>(*this, position + Vector2(40, 10), Vector2(12, 12));
                std::string strNumCount = (sumNumbers <= 9) ? "0" + std::to_string(sumNumbers) : std::to_string(sumNumbers);
                hintTextNum->addComponent<TextComponent>(TextComponent(*hintTextNum, strNumCount.c_str(), colorBlack, font));
                _table.emplace_back(hintTextNum);

                auto hintTextVolt = ActorManager::createActor<Actor>(*this, position + Vector2(55, 45), Vector2(15, 15));
                hintTextVolt->addComponent<TextComponent>(TextComponent(*hintTextVolt, std::to_string(sumVoltorbs).c_str(), colorBlack, font));
                _table.emplace_back(hintTextVolt);

            }

            void createUI()
            {
                _muteButton = ActorManager::createActor<MuteButton>(*this, Vector2(tileSize * 29, tileSize * 0.5f), Vector2(38, 38));
                _muteButton->setMixer(_audioMixer);

                _table.emplace_back(_muteButton);

                createScore();

                createDeductionWheel();
            }

            void createDeductionWheel()
            {
                if (_deductionWheel) return;

                _deductionWheel = ActorManager::createActor<Actor>(*this, center() * tileSize, Vector2(1, 1));
                const int offset = 25;
                auto voltorbButton = createDeductionButton(Vector2(-offset, -offset), Loader::getAsset<SpritesheetAsset>("spritesheet")->getSpriteAt(44), 0);
                auto oneButton = createDeductionButton(Vector2(offset, -offset), Loader::getAsset<SpritesheetAsset>("spritesheet")->getSpriteAt(45), 1);
                auto twoButton = createDeductionButton(Vector2(-offset, offset), Loader::getAsset<SpritesheetAsset>("spritesheet")->getSpriteAt(46), 2);
                auto threeButton = createDeductionButton(Vector2(offset, offset), Loader::getAsset<SpritesheetAsset>("spritesheet")->getSpriteAt(47), 3);
            }

            std::shared_ptr<Button> createDeductionButton(Vector2 pos, std::shared_ptr<Sprite> sprite, int val)
            {
                std::shared_ptr<Button> button = nullptr;

                button = ActorManager::createActor<Button>(*this, Vector2(), Vector2(56, 56), _deductionWheel);
                _deductionWheel->attachChild(button);
                auto transform = button->getComponent<TransformComponent>();
                transform->setLocalPosition(pos);
                button->addComponent<SpriteRendererComponent>(SpriteRendererComponent(*button, sprite));
                // button->addComponent<ColliderComponent>(ColliderComponent(*button, *transform, "ui", true));
                button->addComponent<ColliderComponent>(ColliderComponent(*button, transform->getPositionCentered(), transform->getScale() * 0.3f, "ui", true));
                button->setupButton(button->getComponent<ColliderComponent>(), button->getComponent<SpriteRendererComponent>(), nullptr);

                auto temp = &_selectedCard;
                button->OnClickEnd = ([=](int type)
                {
                    if (type == 2 && temp) 
                    {
                        auto sharedPtr = (*temp);
                        if (sharedPtr) sharedPtr->toggleDeduction(val);
                    }
                });

                return button;
            }

            void createScore()
            {
                std::string str = std::to_string(m_currentScore);
                str += " / ";
                str += std::to_string(m_requiredScore);

                Vector2 textPos = Vector2(center().getX() * (tileSize - 3), 1.0f * tileSize);

                _textShadow = ActorManager::createActor<Actor>(*this, Vector2(textPos.getX() - 2, textPos.getY() + 1), Vector2(14, 14));
                _textShadow->addComponent<TextComponent>(TextComponent(*_textShadow, str.c_str(), SDL_Color{0, 0, 0}, Loader::getAsset<FontAsset>("fontRegular")));
                _table.emplace_back(_textShadow);

                _textCurrentScore = ActorManager::createActor<Actor>(*this, textPos, Vector2(14, 14));
                _textCurrentScore->addComponent<TextComponent>(TextComponent(*_textCurrentScore, str.c_str(), SDL_Color{255, 255, 255}, Loader::getAsset<FontAsset>("fontRegular")));
                _table.emplace_back(_textCurrentScore);
            }

            void update(double dt) override
            {
                if (m_gameOver) 
                {
                    if (m_timeOfDeath + endDelay < getTime()) resetTable();
                }
                else
                {
                    if (_inputProvider->isKeyPressed(SDL_SCANCODE_ESCAPE)) _stageManager->setStage("menu");

                    if (_deductionWheel)
                    {
                        if (_inputProvider->isMouseButtonPressed(2))
                        {
                            if (_deductionWheel->isActive()) return;
                            
                            _deductionWheel->setActive(true);
                            _deductionWheel->getComponent<TransformComponent>()->setPosition(_inputProvider->getMousePosition() + Vector2(-25, -25));
                            for (auto child : _deductionWheel->getChildren())
                            {
                                child->getComponent<ColliderComponent>()->getAABB().setCenter(child->getComponent<TransformComponent>()->getPositionCentered());
                            }
                        }
                        else
                        {
                            if (_deductionWheel->isActive()) _deductionWheel->setActive(false);
                        }
                    }
                }

                Stage::update(dt);
            }

            void sendMessage(std::string msg) override
            {
                if (msg == "gameOver") endGame("Game Over!!");
                else if (msg.find("select_") != std::string::npos)
                {
                    auto x = std::stoi(msg.substr(7, 1));
                    auto y = std::stoi(msg.substr(9, 1));

                    _selectedCard = _cardsArray[x].at(y);
                }
                else
                {
                    m_currentScore *= std::stoi(msg);

                    std::string str = std::to_string(m_currentScore);
                    str += " / ";
                    str += std::to_string(m_requiredScore);
                    _textShadow->getComponent<TextComponent>()->setText(str);
                    _textCurrentScore->getComponent<TextComponent>()->setText(str);


                    if (m_currentScore == m_requiredScore) endGame("Congratulations!!");
                }
            }

            void endGame(std::string endMessage)
            {
                m_gameOver = true;
                _selectedCard = nullptr;

                for (auto &arr : _cardsArray)
                {
                    for (auto &card : arr) 
                    {
                        card->reveal();
                        card = nullptr;
                    }
                }

                Vector2 pos = Vector2(center().getX() * (tileSize - 5),  center().getY() * (tileSize - 3.5f));

                auto shadowMsg = ActorManager::createActor<Actor>(*this, Vector2(pos.getX() -2, pos.getY() + 2), Vector2(14, 14));
                shadowMsg->addComponent<TextComponent>(TextComponent(*shadowMsg, endMessage.c_str(), SDL_Color{0, 0, 0}, Loader::getAsset<FontAsset>("fontLarge")));
                _table.emplace_back(shadowMsg);

                auto msg = ActorManager::createActor<Actor>(*this, pos, Vector2(14, 14));
                msg->addComponent<TextComponent>(TextComponent(*msg, endMessage.c_str(), SDL_Color{0, 104, 71}, Loader::getAsset<FontAsset>("fontLarge")));
                _table.emplace_back(msg);

                m_timeOfDeath = getTime();
                _audioMixer->playMusic(Loader::getAsset<AudioAsset>("musicEnd"));
            }

            void resetTable()
            {
                deleteTable();

                m_currentScore = 1;
                createTable();

                m_gameOver = false;
                _audioMixer->playMusic(Loader::getAsset<AudioAsset>("musicMain"));
            }
            void deleteTable()
            {
                for (auto &it : _table)
                {
                    Collision::removeCollider(it->getID());
                    ActorManager::unregisterActor(*it);
                    it = nullptr;
                }

                _muteButton = nullptr;
                _table.clear();
                for (auto &deduction : _deductionWheel->getChildren())
                {
                    ActorManager::unregisterActor(*deduction);
                }
                ActorManager::unregisterActor(*_deductionWheel);
                _deductionWheel = nullptr;
                ActorManager::updateActorMap();
                _inputProvider->reset();
            }
    };
}