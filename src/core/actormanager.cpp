#include "actormanager.h"
using namespace Core;


std::vector<Actor*> ActorManager::actors;

void ActorManager::registerActor(Actor *a)
{
    actors.push_back(a);
    std::cout << "Actor registered" << std::endl;
}

void ActorManager::deleteActor(Actor actor)
{
    actors.erase(actors.begin() + actor.getID());
}