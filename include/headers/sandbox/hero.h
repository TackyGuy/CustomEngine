#pragma once

#include "herostates.h"
#include "actormanager.h"
#include "actor.h"
#include "spriterenderercomponent.h"
#include "animatorcomponent.h"
#include "rigidbodycomponent.h"
#include "collidercomponent.h"
#include "heroinputcomponent.h"
#include "math.h"

#include "loader.h"

#include <vector>
#include <iostream>

using namespace Core;

namespace Sandbox
{
    class Hero: public Actor
    {
        private:
            HeroStates currentState;
        public:
            ~Hero(){}
            Hero(const Vector2& pos, const Vector2& scale, const int id)
            : Actor(pos, scale, id){}

            void start(Stage& stage) override
            {
                std::shared_ptr<Sprite> sprite = Loader::getAsset<SpritesheetAsset>("hero")->getSpriteAt(2);
                this->addComponent<SpriteRendererComponent>(SpriteRendererComponent(this, sprite.get()));
                this->addComponent<AnimatorComponent>(AnimatorComponent(this, this->getComponent<SpriteRendererComponent>()));
                this->addComponent<ColliderComponent>(ColliderComponent(this, this->getComponent<TransformComponent>(), Vector2(5, 5), "player"));
                this->addComponent<RigidbodyComponent>(RigidbodyComponent(
                    this, this->getComponent<TransformComponent>(), this->getComponent<ColliderComponent>(), RigidbodyComponent::Body::DYNAMIC));
                this->addComponent<HeroInputComponent>(HeroInputComponent(this, &currentState, this->getComponent<RigidbodyComponent>(), 
                    this->getComponent<AnimatorComponent>(), this->getComponent<ColliderComponent>()));

                // TODO Add offset to spritesheet before slicing it
                auto frames = Loader::getAsset<SpritesheetAsset>("hero")->getAllSprites();

                if (frames.size() > 0)
                {
                    AnimatorComponent *animator = this->getComponent<AnimatorComponent>();

                    AnimationSequence idle = AnimationSequence("idle");
                    idle.addFrameToSequence(frames.at(0), 8);
                    idle.addFrameToSequence(frames.at(1));
                    idle.addFrameToSequence(frames.at(2), 8);
                    idle.addFrameToSequence(frames.at(1));
                    idle.setSpeed(0.5f);
                    animator->addSequence(idle);

                    #pragma region Movement animations
                    float runAnimSpeed = 0.6f;
                    AnimationSequence runUp = AnimationSequence("runUp");
                    runUp.addFrameToSequence(frames.at(16), 6);
                    runUp.addFrameToSequence(frames.at(17), 6);
                    runUp.addFrameToSequence(frames.at(18), 6);
                    runUp.addFrameToSequence(frames.at(19), 6);
                    runUp.setSpeed(runAnimSpeed);
                    animator->addSequence(runUp);

                    AnimationSequence runDown = AnimationSequence("runDown");
                    runDown.addFrameToSequence(frames.at(8), 6);
                    runDown.addFrameToSequence(frames.at(9), 6);
                    runDown.addFrameToSequence(frames.at(10), 6);
                    runDown.addFrameToSequence(frames.at(11), 6);
                    runDown.setSpeed(runAnimSpeed);
                    animator->addSequence(runDown);

                    AnimationSequence runSide = AnimationSequence("runSide");
                    runSide.addFrameToSequence(frames.at(12), 6);
                    runSide.addFrameToSequence(frames.at(13), 6);
                    runSide.addFrameToSequence(frames.at(14), 6);
                    runSide.addFrameToSequence(frames.at(15), 6);
                    runSide.setSpeed(runAnimSpeed);
                    animator->addSequence(runSide);
                    #pragma endregion

                    #pragma region Combat animations
                    float attackAnimationSpeed = 0.3f;
                    AnimationSequence attackUp = AnimationSequence("attackUp");
                    attackUp.addFrameToSequence(frames.at(28), 5);
                    attackUp.addFrameToSequence(frames.at(29), 2);
                    attackUp.addFrameToSequence(frames.at(30), 2);
                    attackUp.addFrameToSequence(frames.at(31), 3);
                    attackUp.addFrameToSequence(frames.at(31), 1, "attackEnd");
                    attackUp.setSpeed(attackAnimationSpeed);
                    animator->addSequence(attackUp);

                    AnimationSequence attackSide = AnimationSequence("attackSide");
                    attackSide.addFrameToSequence(frames.at(24), 5);
                    attackSide.addFrameToSequence(frames.at(25), 2);
                    attackSide.addFrameToSequence(frames.at(26), 2);
                    attackSide.addFrameToSequence(frames.at(27), 3);
                    attackSide.addFrameToSequence(frames.at(27), 1, "attackEnd");
                    attackSide.setSpeed(attackAnimationSpeed);
                    animator->addSequence(attackSide);

                    AnimationSequence attackDown = AnimationSequence("attackDown");
                    attackDown.addFrameToSequence(frames.at(20), 5);
                    attackDown.addFrameToSequence(frames.at(21), 2);
                    attackDown.addFrameToSequence(frames.at(22), 2);
                    attackDown.addFrameToSequence(frames.at(23), 3);
                    attackDown.addFrameToSequence(frames.at(23), 1, "attackEnd");
                    attackDown.setSpeed(attackAnimationSpeed);
                    animator->addSequence(attackDown);
                    #pragma endregion

                    animator->playSequence("idle");
                }

                
            }
            void update (double dt, Stage& stage) override
            {
                for (auto component : _components)
                {
                    component.second->update(dt, stage);
                }
            }
    };
}