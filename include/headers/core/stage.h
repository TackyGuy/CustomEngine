#pragma once

#include "inputprovider.h"
#include "actormanager.h"
#include "loader.h"

namespace Core
{
    class Stage
    {
        private:
            InputProvider m_inputProvider;
            double m_elapsedTime;
        protected:
            const int stageWidth;
            const int stageHeight;
            const int tileSize;

            Vector2 center() const;
        public:
            ~Stage(){};
            Stage(int width, int height, int size) : stageWidth(width), stageHeight(height), tileSize(size)
            {
                m_inputProvider = InputProvider();
                m_inputProvider.initialize();
            }

            /**
             * @brief The first method called on the stage. It allows to load resources before creating any actors.
             * 
             */
            virtual void preload(){};
            /**
             * @brief Initialize the stage and instantiate the actors here.
             * 
             */
            virtual void init()
            {
                for (Actor *actor : ActorManager::actors)
                {
                    actor-> start(*this);
                }
            }
            /**
             * @brief Keep track of the elapsed time and updates all the actors in the stage.
             * 
             * @param dt DeltaTime
             */
            virtual void update(double dt)
            {
                m_elapsedTime += dt;
                for (Actor *actor : ActorManager::actors)
                {
                    actor->update(dt, *this);
                }
            }

            InputProvider *getInputProvider();
            const double getTime() const;
    };
}

