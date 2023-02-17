#include "actormanager.hpp"
using namespace Core;

void ActorManager::registerActor(const std::shared_ptr<Actor> actor)
{
    s_actors.emplace(actor->getID(), std::move(actor));
    // std::cout << "Actor registered" << std::endl;
}

void ActorManager::unregisterActor(Actor actor)
{
    if (actor.isActive()) s_activeActors.erase(actor.getID());
    s_actors[actor.getID()] = nullptr;
}
void ActorManager::unregisterAllActors()
{
    for (auto &it : s_actors)
    {
        if (it.second->isActive()) s_activeActors.erase(it.second->getID());
        it.second = nullptr;
    }
    
}

void ActorManager::updateActorMap()
{
    for (auto it = s_actors.cbegin(); it != s_actors.cend();)
    {
        if (!(it->second)) s_actors.erase(it++);
        else 
        {
            auto actor = it->second;

            bool active = actor->isActive();

            if (s_activeActors.find(it->first) == s_activeActors.end())
            {
                if (active) s_activeActors.emplace(it->first, it->second);
            }
            else 
            {
                if (!active) s_activeActors.erase(it->first);
            }
            
            ++it;
        }
    }
}