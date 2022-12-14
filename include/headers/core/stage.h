#pragma once

#include "inputprovider.h"
#include "audiomixer.h"
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
            
            AudioMixer *_audioMixer = nullptr;

            Vector2 center() const;
        public:
            ~Stage(){};
            Stage(int width, int height, int size, AudioMixer *mixer) : stageWidth(width), stageHeight(height), tileSize(size), _audioMixer(mixer)
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

            /**
             * @brief Sends a message to the stage
             * 
             * @param msg The message as a string
             */
            virtual void sendMessage(std::string msg) = 0;

            InputProvider *getInputProvider();
            AudioMixer *getAudioMixer();
            const double getTime() const;
    };
}

