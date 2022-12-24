#include "actormanager.h"
using namespace Core;

void ActorManager::registerActor(std::shared_ptr<Actor> a)
{
    s_actors.push_back(a);
    // std::cout << "Actor registered" << std::endl;
}

void ActorManager::deleteActor(Actor actor)
{
    s_actors.erase(s_actors.begin() + actor.getID());
}