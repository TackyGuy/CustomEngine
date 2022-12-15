#pragma once

#include "actor.h"

namespace Core
{
    class ActorManager
    {
        private:

        public:
            // A vector holding pointers to all the valid Actors.
            inline static std::vector<std::shared_ptr<Actor>> actors;

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
            static std::shared_ptr<T> createActor(const Vector2& pos, const Vector2& scale)
            {
                std::shared_ptr<T> newActor(new T(pos, scale, actors.size()));

                actors.push_back(newActor);
                // std::cout << "Actor created" << std::endl;

                return newActor;
            }
            /**
             * @brief Registers an Actor object.
             * 
             * @param a The Actor object to register
             */
            static void registerActor(std::shared_ptr<Actor> a);
            /**
             * @brief Unregister and delete the specified Actor object.
             * 
             * @param actor The Actor object to delete.
             */
            static void deleteActor(Actor actor);
    };
}