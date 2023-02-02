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
             * @param actor The actor that implements the actor interface
             */
            InputComponent(const ActorInterface& actor) : BaseComponent(actor){};

            InputComponent(InputComponent& other) = default;
            InputComponent(InputComponent&& other) = default;

            virtual void update(double dt, Stage& stage)
            {}
    };
}