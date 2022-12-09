#pragma once

#include "herostates.h"
#include "inputcomponent.h"
#include "rigidbodycomponent.h"
#include "animatorcomponent.h"
#include "collidercomponent.h"

namespace Sandbox
{
    class HeroInputComponent : public Core::InputComponent
    {
        private:
            HeroStates *heroStates = nullptr;

            Core::RigidbodyComponent *_rigidbody = nullptr;
            Core::AnimatorComponent  *_animator = nullptr;
            Core::ColliderComponent *_collider = nullptr;

            double m_runSpeed = 85;

            double m_lastAttack = -100;
            const double attackRate = 0.4;
        public:

            ~HeroInputComponent(){};
            HeroInputComponent(Core::BroadcasterInterface *broadcaster, HeroStates *states, Core::RigidbodyComponent *rigidbody, Core::AnimatorComponent *animator, Core::ColliderComponent *collider)
            : Core::InputComponent(broadcaster), heroStates(states), _rigidbody(rigidbody), _animator(animator), _collider(collider)
            {}

            virtual void update(double dt, Core::Stage& stage) override
            {
                Core::InputProvider *pInputProvider = stage.getInputProvider();
                Core::Vector2 velocity;

                if (pInputProvider->isKeyPressed(SDL_SCANCODE_UP))
                {
                    velocity = Core::Vector2(0, -m_runSpeed * dt);
                }
                else if (pInputProvider->isKeyPressed(SDL_SCANCODE_RIGHT))
                {
                    velocity = Core::Vector2(m_runSpeed * dt, 0);
                    if (!heroStates->hasFlag(COMBAT_STATE)) _animator->flipRenderer(false);
                }
                else if (pInputProvider->isKeyPressed(SDL_SCANCODE_DOWN))
                {
                    velocity = Core::Vector2(0, m_runSpeed * dt);
                }
                else if (pInputProvider->isKeyPressed(SDL_SCANCODE_LEFT))
                {
                    velocity = Core::Vector2(-m_runSpeed * dt, 0);
                    if (!heroStates->hasFlag(COMBAT_STATE)) _animator->flipRenderer(true);
                }

                if (!heroStates->hasFlag(COMBAT_STATE) && pInputProvider->isKeyPressed(SDL_SCANCODE_Z))
                {
                    double curTime = stage.getTime();
                    if (m_lastAttack + attackRate < curTime)
                    {
                        m_lastAttack = curTime;
                        heroStates->setFlag(COMBAT_STATE);
                    }
                }

                if (velocity.getX() != 0 || velocity.getY() != 0) heroStates->setFlag(MOVE_STATE);
                else heroStates->setFlag(MOVE_STATE, false);

                // std::cout << *heroStates << std::endl;
                if (heroStates->hasFlag(COMBAT_STATE)) 
                {
                    velocity.multiply(0.35f);
                }
                animationManager(velocity);
                _rigidbody->setVelocity(velocity);
            }

            /**
             * @brief Call for the appropriate animation based on the current states of the hero
             * 
             * @param velocity The velocity of the hero character
             */
            void animationManager(const Core::Vector2& velocity)
            {
                if (heroStates->hasFlag(COMBAT_STATE))
                {
                    if (_animator->getCurrentSequence()->getName().find("attack") == std::string::npos)
                    {
                        if (velocity.getY() < 0) _animator->playSequence("attackUp");
                        else if (velocity.getY() > 0) _animator->playSequence("attackDown");
                        else _animator->playSequence("attackSide");
                    }
                }
                else if (heroStates->hasFlag(MOVE_STATE))
                {
                    if (velocity.getY() < 0) _animator->playSequence("runUp");
                    else if (velocity.getY() > 0) _animator->playSequence("runDown");
                    else _animator->playSequence("runSide");
                }
                else if (heroStates->hasFlag(IDLE_STATE)) _animator->playSequence("idle");
            }

            virtual void OnMessage(const std::string& msg, const size_t sender) override
            {
                if (sender == Core::AnimatorComponent::Type)
                {
                    if (msg == "attackEnd")
                    {
                        heroStates->setFlag(COMBAT_STATE, false);
                    }
                    if (msg == "animationEnd")
                    {
                        //
                    }
                }
            }
    };
}