#pragma once

#include <string>

namespace Core
{
    /**
     * @brief Interface that allows to broadcastMessages
     * 
     */
    class BroadcasterInterface
    {
        public:
            virtual void broadcastMessage(const std::string& msg, const size_t sender) const = 0;
    };
}