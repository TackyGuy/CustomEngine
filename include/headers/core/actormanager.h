#pragma once

#include <unordered_map>

#include "actor.h"

namespace Core
{
    class ActorManager
    {
        private:

        public:
            inline static std::unordered_map<int, std::shared_ptr<Actor>> s_actors;
            // Has to be ordered so all the elements are rendered
            inline static std::map<int, std::weak_ptr<Actor>> s_activeActors;

            /**
             * @brief Create an Actor object of type T at the specified position and
             * with the specified scale and registers it.
             * 
             * @tparam T The type of Actor
             * @param pos The position the Actor object should be placed at
             * @param scale The scale the Actor object should have
             * @return T* A pointer of type T pointing to the new Actor object.
             */
            template <class T>
            static std::shared_ptr<T> createActor(Stage &stage, const Vector2& pos, const Vector2& scale, const std::shared_ptr<Actor> parent = nullptr)
            {
                auto newActor = std::make_shared<T>(T(stage, s_actors.size(), pos, scale, parent));
                newActor->setActive(true);
                newActor->init();
                
                // std::cout << "Actor(" << s_actors.size() << ") created" << std::endl;
                registerActor(newActor);

                return newActor;
            }
            /**
             * @brief Registers an Actor object.
             * 
             * @param a The Actor object to register
             */
            static void registerActor(const std::shared_ptr<Actor> actor);
            /**
             * @brief Unregister the specified Actor object.
             * 
             * @param actor The Actor object to delete.
             */
            static void unregisterActor(Actor actor);
            /**
             * @brief Unregister all the Actor objects.
             * 
             */
            static void unregisterAllActors();

            static void updateActorMap();
            static void updateActiveActors();
    };
}