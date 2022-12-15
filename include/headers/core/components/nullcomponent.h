#pragma once

#include "basecomponent.h"

namespace Core
{
    class NullComponent : public BaseComponent
    {
        private:
            
        public:
            static const size_t Type;
            const size_t getType() const override
            {
                return Type;
            }

            NullComponent(const BroadcasterInterface& p_broadcaster) : BaseComponent(p_broadcaster)
            {}
            ~NullComponent()
            {}
    };
}