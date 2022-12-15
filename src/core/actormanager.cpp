#include "actormanager.h"
using namespace Core;

void ActorManager::registerActor(std::shared_ptr<Actor> a)
{
    actors.push_back(a);
    std::cout << "Actor registered" << std::endl;
}

void ActorManager::deleteActor(Actor actor)
{
    actors.erase(actors.begin() + actor.getID());
}