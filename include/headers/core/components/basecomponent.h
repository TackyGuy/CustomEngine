#pragma once

#include <memory>
#include <iostream>
#include <string>
#include <unordered_map>

#include "broadcasterinterface.h"

#define TYPE

namespace Core
{
    class Stage;
    class BaseComponent
    {
        private:
            bool m_active;
        protected:
           const BroadcasterInterface& broadcaster;
        public:
            static const size_t Type;

            /**
             * @brief Construct a new Base Component object.
             * 
             * @param broadcaster A reference to the actor that holds the component
             */
            BaseComponent(const BroadcasterInterface& p_broadcaster) : broadcaster(p_broadcaster)
            {}
            virtual ~BaseComponent() = default;

            /**
             * @brief Updates the component.
             * 
             * @param dt DeltaTime as a double
             * @param stage A reference to the current stage
             */
            virtual void update(double dt, Stage& stage)
            {}

            virtual const size_t getType() const = 0;
            
            /**
             * @brief Check if the type of this component is the same as the one entered as a parameter.
             * 
             * @param classType The component type to check against
             * @return true if both components are of the same type.
             * @return false if both components aren't of the same type.
             */
            bool IsClassType(const std::size_t classType)
            {
                return classType == Type;
            }

            /**
             * @brief Is this component currently active?
             * 
             * @return true if is active
             * @return false if is not active
             */
            bool isActive();
            // Sets the active state of this component.
            void setActive(bool state);

            /**
             * @brief Sends a message to to the actor that holds the component.
             * The message is then broadcasted to all the other components.
             * @param msg The message to send
             */
            void sendMessage(const std::string& msg);
            /**
             * @brief How the component should act upon receiving a message.
             * 
             * @param msg The received message
             */
            virtual void OnMessage(const std::string& msg, const size_t sender)
            {
                // std::cout << "Message received: " << msg << " from: " << sender << std::endl;
            }
            
    };
}