#pragma once

#include "SDL.h"
#include "SDL_image.h"

#include "basecomponent.h"
#include "spriterenderercomponent.h"
#include "animationsequence.h"

#include <iostream>
#include <unordered_map>

namespace Core
{
    class AnimatorComponent: public BaseComponent
    {
        private:
            bool m_paused;
            std::string m_lastMessage;
            std::unordered_map<std::string, AnimationSequence> m_sequences;
            AnimationSequence *m_currentSequence;

            SpriteRendererComponent *_spriteRenderer;

            bool isValid(const std::string& key);
        public:
            static const size_t Type;
            const size_t getType() const override
            {
                return Type;
            }

            ~AnimatorComponent(){}
            /**
             * @brief Construct a new Animator Component object.
             * 
             * @param broadcaster The actor that implements the IBroadcaster interface
             * @param spriteRenderer The SpriteRendererComponent to animate
             */
            AnimatorComponent(BroadcasterInterface *broadcaster, SpriteRendererComponent *spriteRenderer) : BaseComponent(broadcaster)
            {
                _spriteRenderer = spriteRenderer;
            }

            virtual void update(double dt, Stage& stage) override
            {
                _spriteRenderer->setSprite(m_currentSequence->getCurrentFrame());

                auto strEvent = m_currentSequence->getEvent();
                if (m_lastMessage != strEvent)
                {
                    m_lastMessage = strEvent;
                    // _broadcaster->broadcastMessage(m_lastMessage, Type);
                    sendMessage(m_lastMessage);
                }
            }


            /**
             * @brief Adds an animation sequence to the map of animations.
             * 
             * @param sequence The animation sequence to add
             */
            void addSequence(const AnimationSequence& sequence);
            /**
             * @brief Sets the current AnimationSequence to the desired one.
             * 
             * @param key The key of the animation sequence
             */
            void playSequence(const std::string& key);
            /**
             * @brief Get a pointer to the AnimationSequence object.
             * 
             * @param key The key of the animation sequence
             * @return AnimationSequence* 
             */
            AnimationSequence *getSequence(const std::string& key);
            /**
             * @brief Get a pointer to the Current AnimationSequence object.
             * 
             * @return AnimationSequence* 
             */
            AnimationSequence *getCurrentSequence();
            /**
             * @brief Flips the SpriteRendererComponent on its horizontal axis.
             * 
             * @param val Sets the value of the flipped state of the SpriteRendererComponent
             */
            void flipRenderer(bool val);
    };
}