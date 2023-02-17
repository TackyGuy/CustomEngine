#include "basecomponent.hpp"
using namespace Core;

const size_t BaseComponent::Type = 0;

bool BaseComponent::isActive()
{
    return m_active;
}

void BaseComponent::setActive(bool state)
{
    m_active = state;
}

void BaseComponent::sendMessage(const std::string& msg)
{
    if (!msg.empty()) actorInterface.broadcastMessage(msg, getType());
}
