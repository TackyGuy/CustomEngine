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
            double m_elapsedTime;
        protected:
            const int stageWidth;
            const int stageHeight;
            const int tileSize;
            
            std::shared_ptr<AudioMixer> _audioMixer = nullptr;
            std::shared_ptr<InputProvider> _inputProvider = nullptr;

            Vector2 center() const;
        public:
            virtual ~Stage(){}

            Stage(int width, int height, int size, std::shared_ptr<AudioMixer> mixer) : stageWidth(width), stageHeight(height), tileSize(size), _audioMixer(mixer)
            {
                _inputProvider = std::make_shared<InputProvider>(InputProvider());
                _inputProvider->initialize();
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
            virtual void start()
            {
                for (auto actor : ActorManager::s_actors)
                {
                    if (actor.second) actor.second->start();
                }
            }
            /**
             * @brief Keep track of the elapsed time and updates all the actors in the stage.
             * 
             * @param dt DeltaTime
             */
            virtual void update(double dt)
            {
                ActorManager::updateActorMap();

                m_elapsedTime += dt;
                for (auto it : ActorManager::s_activeActors)
                {
                    auto actor = it.second.lock();
                    if (actor) 
                    {
                        if (actor->isReady()) actor->update(dt);
                        else actor->start();
                        
                    }
                }
            }

            /**
             * @brief Sends a message to the stage
             * 
             * @param msg The message as a string
             */
            virtual void sendMessage(std::string msg) = 0;

            /**
             * @brief Get a shared_ptr to the InputProvider
             * 
             * @return std::shared_ptr<InputProvider> 
             */
            std::shared_ptr<InputProvider> getInputProvider();
            /**
             * @brief Get a shared_ptr to the AudioMixer
             * 
             * @return std::shared_ptr<AudioMixer> 
             */
            std::shared_ptr<AudioMixer> getAudioMixer();
            /**
             * @brief Get the current time in the stage
             * 
             * @return const double 
             */
            const double getTime() const;
    };
}

