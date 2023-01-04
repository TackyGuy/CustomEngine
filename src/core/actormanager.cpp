#include "actormanager.h"
using namespace Core;

void ActorManager::registerActor(const std::shared_ptr<Actor> actor)
{
    s_actors.emplace(actor->getID(), std::move(actor));
    // std::cout << "Actor registered" << std::endl;
}

void ActorManager::deleteActor(Actor actor)
{
    s_actors.erase(actor.getID());
    if (actor.isActive()) s_activeActors.erase(actor.getID());
}


void ActorManager::updateActiveActors()
{
    for (auto iterator : s_actors)
    {
        auto actor = iterator.second;
        bool active = actor->isActive();

        if (s_activeActors.find(iterator.first) == s_activeActors.end())
        {
            if (active) s_activeActors.emplace(iterator.first, iterator.second);
        }
        else 
        {
            if (!active) s_activeActors.erase(iterator.first);
        }
    }
}