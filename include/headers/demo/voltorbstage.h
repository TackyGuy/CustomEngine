#pragma once

#include <vector>
#include <array>
#include <random>

#include "stage.h"
#include "card.h"

using namespace Core;
namespace Demo1
{
    class VoltorbStage: public Stage
    {
        private:
            bool m_gameOver = false;
            uint16_t m_currentScore;
            uint16_t m_requiredScore;
            // Represents the game table
            std::vector<Actor*> _table;
            const int CARDS_PER_ROW = 5;
            const int CARDS_PER_COLUMN = 5;
            std::array<std::array<int, 5>, 5> cardsArray;

            SDL_Color colorBlack = {0, 0, 0};
        public:
            ~VoltorbStage(){};
            VoltorbStage(AudioMixer *mixer) : Stage(32, 23, 32, mixer){};

            void preload() override
            {
                Loader::loadAsset("spritesheet", new SpritesheetAsset("res/sprites/demo/spritesheet.png", 28, 28));

                Loader::loadAsset("musicMain", new AudioAsset("res/sounds/gameCorner.mp3", true));
                Loader::loadAsset("musicSlots", new AudioAsset("res/sounds/slotsWin.mp3", true));
                Loader::loadAsset("sfxClick", new AudioAsset("res/sounds/demo/click.wav", false));
                Loader::loadAsset("sfxSelect", new AudioAsset("res/sounds/demo/select.wav", false));
                Loader::loadAsset("sfxCard1", new AudioAsset("res/sounds/demo/card1.wav", false));
                Loader::loadAsset("sfxCard2", new AudioAsset("res/sounds/demo/card2.wav", false));
                Loader::loadAsset("sfxCard3", new AudioAsset("res/sounds/demo/card3.wav", false));
                Loader::loadAsset("sfxExplosion", new AudioAsset("res/sounds/demo/explosion.wav", false));

                Loader::loadAsset("fontSmall", new FontAsset("res/fonts/weiholmir_regular.ttf", 12));
                Loader::loadAsset("fontRegular", new FontAsset("res/fonts/weiholmir_regular.ttf", 14));
                Loader::loadAsset("fontLarge", new FontAsset("res/fonts/weiholmir_regular.ttf", 18));
            }

            void init() override
            {
                std::cout << "Welcome to Voltorb Flip!" << std::endl;
                createTable();

                _audioMixer->setMusicVolume(2);
                _audioMixer->playMusic(Loader::getAsset<AudioAsset>("musicMain"));
                _audioMixer->setSoundVolume(1);

                Stage::init();
            }

            void createTable()
            {
                Actor *backgroundProp = ActorManager::createActor<Actor>(Vector2(0, 0), Vector2(stageWidth * tileSize, stageHeight * tileSize));
                backgroundProp->addComponent<SpriteRendererComponent>(SpriteRendererComponent(backgroundProp, Loader::getAsset<SpritesheetAsset>("spritesheet")->getSpriteAt(0).get()));
                _table.emplace_back(backgroundProp);

                m_requiredScore = 1;

                placeCards();
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

                SpritesheetAsset *spritesheet = Loader::getAsset<SpritesheetAsset>("spritesheet");

                // Creates the cards and wires
                for (int x = 0; x < CARDS_PER_ROW; x++)
                {
                    for (int y = 0; y < CARDS_PER_COLUMN; y++)
                    {
                        Vector2 pos = Vector2(startX + x * (cardSize + margin), startY + y * (cardSize + margin));
                        // We create the visual wires here also
                        Actor *wireY = ActorManager::createActor<Actor>(pos + Vector2(0, 15), Vector2(cardSize, cardSize));
                        wireY->addComponent<SpriteRendererComponent>(SpriteRendererComponent(wireY, spritesheet->getSpriteAt(32 + x).get()));
                        _table.emplace_back(wireY);

                        Actor *wireX = ActorManager::createActor<Actor>(pos + Vector2(15, 0), Vector2(cardSize, cardSize));
                        wireX->addComponent<SpriteRendererComponent>(SpriteRendererComponent(wireX, spritesheet->getSpriteAt(37 + y).get()));
                        _table.emplace_back(wireX);

                        Card *card = ActorManager::createActor<Card>(pos, Vector2(cardSize, cardSize));

                        int cardIndex = distrCardFaces(randEngine);
                        cardsArray[x].at(y) = cardIndex;
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
                            spritesheet->getSpriteAt(cardIndex + spriteOffset).get(), 
                            spritesheet->getSpriteAt(spriteOffset).get(), 
                            spritesheet->getSpriteAt(21).get(),
                            Loader::getAsset<AudioAsset>(sfxName),
                            cardIndex
                            );

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
                        int cardValue = cardsArray[i].at(j);
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
                        int cardValue = cardsArray[j].at(i);
                        if (cardValue == 4) totalVoltorbs++;
                        else totalNums += cardValue;
                    }

                    createHint(totalNums, totalVoltorbs, i + 22, Vector2(startX + CARDS_PER_ROW * (cardSize + margin), startY + i * (cardSize + margin)),Vector2(cardSize, cardSize));
                }
            }

            void createHint(int sumNumbers, int sumVoltorbs, int spriteIndex, Vector2 position, Vector2 size)
            {
                auto font = Loader::getAsset<FontAsset>("fontRegular");

                Actor *hintCard = ActorManager::createActor<Actor>(position, size);
                hintCard->addComponent<SpriteRendererComponent>(SpriteRendererComponent(hintCard, Loader::getAsset<SpritesheetAsset>("spritesheet")->getSpriteAt(spriteIndex).get()));
                _table.emplace_back(hintCard);

                Actor *hintTextNum = ActorManager::createActor<Actor>(position + Vector2(40, 10), Vector2(12, 12));
                std::string strNumCount = (sumNumbers <= 9) ? "0" + std::to_string(sumNumbers) : std::to_string(sumNumbers);
                hintTextNum->addComponent<TextComponent>(TextComponent(hintTextNum, strNumCount.c_str(), colorBlack, font));
                _table.emplace_back(hintTextNum);

                Actor *hintTextVolt = ActorManager::createActor<Actor>(position + Vector2(55, 45), Vector2(15, 15));
                hintTextVolt->addComponent<TextComponent>(TextComponent(hintTextVolt, std::to_string(sumVoltorbs).c_str(), colorBlack, font));
                _table.emplace_back(hintTextVolt);

            }

            void update(double dt) override
            {
                if (!m_gameOver)
                {
                    Stage::update(dt);
                }
                else
                {
                    resetTable();
                }
            }

            void sendMessage(std::string msg) override
            {
                if (msg == "gameOver")
                {
                    m_gameOver = true;
                    std::cout << "Game Over!" << std::endl;
                }
                else
                {
                    m_currentScore *= std::stoi(msg);
                    if (m_currentScore == m_requiredScore) m_gameOver = true;
                }
            }

            void resetTable()
            {
                // std::vector<Actor*> temp = _table;
                for (int i = 0; i < _table.size(); i++)
                {
                    ActorManager::deleteActor(*_table[i]);
                }

                _table.clear();

                m_currentScore = 0;
                m_gameOver = false;

                createTable();
            }
    };
}