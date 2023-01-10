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
            
            virtual ~InputComponent(){}
            /**
             * @brief Construct a new InputComponent object.
             * 
             * @param p_broadcaster The actor that implements the IBroadcaster interface
             */
            InputComponent(const BroadcasterInterface& p_broadcaster) : BaseComponent(p_broadcaster){};

            InputComponent(InputComponent& other) = default;
            InputComponent(InputComponent&& other) = default;

            virtual void update(double dt, Stage& stage)
            {}
    };
}