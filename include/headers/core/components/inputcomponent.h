#pragma once

#include "inputprovider.h"
#include "basecomponent.h"
#include "SDL.h"

#include <iostream>

namespace Core
{
    class InputComponent: public BaseComponent
    {
        private:

        public:
            static const size_t Type;
            const size_t getType() const override
            {
                return Type;
            }
            
            virtual ~InputComponent() = default;
            InputComponent(const BroadcasterInterface& p_broadcaster) : BaseComponent(p_broadcaster){};

            virtual void update(double dt, Stage& stage)
            {}
    };
}