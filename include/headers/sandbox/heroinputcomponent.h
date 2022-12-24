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
            HeroStates& heroStates;

            std::shared_ptr<Core::RigidbodyComponent> _rigidbody = nullptr;
            std::shared_ptr<Core::AnimatorComponent> _animator = nullptr;

            const double m_runSpeed = 85;

            double m_lastAttack = -100;
            const double attackRate = 0.4;
        public:

            ~HeroInputComponent(){};
            HeroInputComponent(const Core::BroadcasterInterface& p_broadcaster, HeroStates& states, std::shared_ptr<Core::RigidbodyComponent> rigidbody, std::shared_ptr<Core::AnimatorComponent> animator)
            : Core::InputComponent(p_broadcaster), heroStates(states), _rigidbody(rigidbody), _animator(animator)
            {}

            HeroInputComponent(HeroInputComponent& other)
            : InputComponent(other.broadcaster), heroStates(other.heroStates)
            {
                _rigidbody = other._rigidbody;
                _animator = other._animator;
            }
            HeroInputComponent(HeroInputComponent&& other):
                InputComponent(other.broadcaster), heroStates(other.heroStates)
            {
                _rigidbody = other._rigidbody;
                _animator = other._animator;

                other._rigidbody = nullptr;
                other._animator = nullptr;
            }

            virtual void update(double dt, Core::Stage& stage) override
            {
                auto inputProvider = stage.getInputProvider();
                Core::Vector2 velocity;

                if (inputProvider->isKeyPressed(SDL_SCANCODE_UP))
                {
                    velocity = Core::Vector2(0, -m_runSpeed * dt);
                }
                else if (inputProvider->isKeyPressed(SDL_SCANCODE_RIGHT))
                {
                    velocity = Core::Vector2(m_runSpeed * dt, 0);
                    if (!heroStates.hasFlag(COMBAT_STATE)) _animator->flipRenderer(false);
                }
                else if (inputProvider->isKeyPressed(SDL_SCANCODE_DOWN))
                {
                    velocity = Core::Vector2(0, m_runSpeed * dt);
                }
                else if (inputProvider->isKeyPressed(SDL_SCANCODE_LEFT))
                {
                    velocity = Core::Vector2(-m_runSpeed * dt, 0);
                    if (!heroStates.hasFlag(COMBAT_STATE)) _animator->flipRenderer(true);
                }

                if (!heroStates.hasFlag(COMBAT_STATE) && inputProvider->isKeyPressed(SDL_SCANCODE_Z))
                {
                    double curTime = stage.getTime();
                    if (m_lastAttack + attackRate < curTime)
                    {
                        m_lastAttack = curTime;
                        heroStates.setFlag(COMBAT_STATE);
                    }
                }

                if (velocity.getX() != 0 || velocity.getY() != 0) heroStates.setFlag(MOVE_STATE);
                else heroStates.setFlag(MOVE_STATE, false);

                // std::cout << *heroStates << std::endl;
                if (heroStates.hasFlag(COMBAT_STATE)) 
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
                if (heroStates.hasFlag(COMBAT_STATE))
                {
                    if (_animator->getCurrentSequence()->getName().find("attack") == std::string::npos)
                    {
                        if (velocity.getY() < 0) _animator->playSequence("attackUp");
                        else if (velocity.getY() > 0) _animator->playSequence("attackDown");
                        else _animator->playSequence("attackSide");
                    }
                }
                else if (heroStates.hasFlag(MOVE_STATE))
                {
                    if (velocity.getY() < 0) _animator->playSequence("runUp");
                    else if (velocity.getY() > 0) _animator->playSequence("runDown");
                    else _animator->playSequence("runSide");
                }
                else if (heroStates.hasFlag(IDLE_STATE)) _animator->playSequence("idle");
            }

            virtual void OnMessage(const std::string& msg, const size_t sender) override
            {
                if (sender == Core::AnimatorComponent::Type)
                {
                    if (msg == "attackEnd")
                    {
                        heroStates.setFlag(COMBAT_STATE, false);
                    }
                    if (msg == "animationEnd")
                    {
                        //
                    }
                }
            }
    };
}