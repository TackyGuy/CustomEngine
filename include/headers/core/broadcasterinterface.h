#pragma once

#include <string>

namespace Core
{
    class BroadcasterInterface
    {
        public:
            virtual void broadcastMessage(const std::string& msg, const size_t sender) = 0;
    };
}