#pragma once

#include <string>

namespace Core
{
    /**
     * @brief Interface that allows to components to interact with their actor
     * 
     */
    class ActorInterface
    {
        public:
            virtual void broadcastMessage(const std::string& msg, const size_t sender) const = 0;
            virtual const int getID() const = 0;
    };
}