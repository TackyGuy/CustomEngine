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
            // Represents the game table
            std::vector<Actor*> _table;
            const int CARDS_PER_ROW = 5;
            const int CARDS_PER_COLUMN = 5;
            std::array<std::array<int, 5>, 5> cardsArray;

            SDL_Color colorBlack = {0, 0, 0};

            uint16_t m_currentScore;
        public:
            ~VoltorbStage(){};
            VoltorbStage(AudioMixer *mixer) : Stage(32, 23, 32, mixer){};

            void preload() override
            {
                Loader::loadAsset("spritesheet", new SpritesheetAsset("res/sprites/demo/spritesheet.png", 28, 28));

                Loader::loadAsset("musicMain", new AudioAsset("res/sounds/gameCorner.mp3", true));
                Loader::loadAsset("musicSlots", new AudioAsset("res/sounds/slotsWin.mp3", true));

                Loader::loadAsset("fontSmall", new FontAsset("res/fonts/weiholmir_regular.ttf", 12));
                Loader::loadAsset("fontRegular", new FontAsset("res/fonts/weiholmir_regular.ttf", 16));
                Loader::loadAsset("fontLarge", new FontAsset("res/fonts/weiholmir_regular.ttf", 24));
            }

            void init() override
            {
                std::cout << "Welcome to Voltorb Flip!" << std::endl;
                createTable();

                Stage::init();
            }

            void createTable()
            {
                Actor *backgroundProp = ActorManager::createActor<Actor>(Vector2(0, 0), Vector2(stageWidth * tileSize, stageHeight * tileSize));
                backgroundProp->addComponent<SpriteRendererComponent>(SpriteRendererComponent(backgroundProp, Loader::getAsset<SpritesheetAsset>("spritesheet")->getSpriteAt(0).get()));
                _table.emplace_back(backgroundProp);

                placeCards();
            }

            void placeCards()
            {
                std::random_device rd;
                std::default_random_engine randEngine(rd());
                std::uniform_int_distribution<int> distrCardFaces(0, 3);

                int startX = 9 * tileSize;
                int startY = 3 * tileSize;
                int cardSize = 80;
                int margin = 10;

                SpritesheetAsset *spritesheet = Loader::getAsset<SpritesheetAsset>("spritesheet");
                std::vector<Sprite*> possibleCards;
                if (spritesheet)
                {
                    possibleCards.emplace_back(spritesheet->getSpriteAt(1).get());
                    possibleCards.emplace_back(spritesheet->getSpriteAt(2).get());
                    possibleCards.emplace_back(spritesheet->getSpriteAt(3).get());
                    possibleCards.emplace_back(spritesheet->getSpriteAt(4).get());
                }

                // Creates the cards
                for (int row = 0; row < CARDS_PER_ROW; row++)
                {
                    for (int column = 0; column < CARDS_PER_COLUMN; column++)
                    {
                        Vector2 pos = Vector2(startX + row * (cardSize + margin), startY + column * (cardSize + margin));

                        Card *card = ActorManager::createActor<Card>(pos, Vector2(cardSize, cardSize));

                        int cardValue = 0;
                        int cardIndex = distrCardFaces(randEngine);
                        switch (cardIndex)
                        {
                            case 3:
                                cardValue = 0;
                            break;
                            case 2:
                                cardValue = 3;
                            break;
                            case 1:
                                cardValue = 2;
                            break;
                            default:
                                cardValue = 1;
                        }
                        cardsArray[row].at(column) = cardValue;

                        card->setFaceSprite(possibleCards[cardIndex]);

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
                        if (cardValue == -1) totalVoltorbs++;
                        else totalNums += cardValue;
                    }

                    createHint(totalNums, totalVoltorbs, Vector2(startX + i * (cardSize + margin), startY + CARDS_PER_COLUMN * (cardSize + margin)),Vector2(cardSize, cardSize));
                }

                for (int i = 0; i < CARDS_PER_COLUMN; i++)
                {
                    int totalNums = 0;
                    int totalVoltorbs = 0;
                    for (int j = 0; j < CARDS_PER_ROW; j++)
                    {
                        int cardValue = cardsArray[j].at(i);
                        if (cardValue == -1) totalVoltorbs++;
                        else totalNums += cardValue;
                    }

                    createHint(totalNums, totalVoltorbs, Vector2(startX + CARDS_PER_ROW * (cardSize + margin), startY + i * (cardSize + margin)),Vector2(cardSize, cardSize));
                }
            }

            void createHint(int sumNumbers, int sumVoltorbs, Vector2 position, Vector2 size)
            {
                auto font = Loader::getAsset<FontAsset>("fontRegular");

                Actor *hintCard = ActorManager::createActor<Actor>(position, size);
                hintCard->addComponent<SpriteRendererComponent>(SpriteRendererComponent(hintCard, Loader::getAsset<SpritesheetAsset>("spritesheet")->getSpriteAt(5).get()));

                Actor *hintText = ActorManager::createActor<Actor>(position, Vector2(15, 15));

                hintText->addComponent<TextComponent>(TextComponent(hintText, std::to_string(sumNumbers).c_str(), colorBlack, font));
                // hintColumn->addComponent<TextComponent>(TextComponent(hintColumn, std::to_string(hintC.second).c_str(), colorBlack, font));
            }

            void cleanTable()
            {

            }
    };
}