#pragma once

#include "SDL.h"
#include <string.h>
#include <iostream>

#include "mathutils.h"
#include "userinterface.h"

namespace Core
{
    class InputProvider
    {
        private:
            Uint8 *_previousInput = nullptr;
            Uint8 *_currentInput = nullptr;

            Uint32 m_previousMouseState;
            Uint32 m_mouseState;
            Vector2 m_mousePos;

            UserInterface *_currentHovered = nullptr;
            
        public:
            ~InputProvider()
            {
                delete _previousInput;
                delete _currentInput;

                delete _currentHovered;
                _currentHovered = nullptr;
            }
            InputProvider(){}

            void initialize();
            void reset();
            void handleInputs();
            void handleKeyboard();
            void handleMouse();
            void handleEventsUI();

            // Returns true if the key at keyCode is pressed
            bool isKeyTriggered(const SDL_Scancode keyCode) const;
            bool isKeyPressed(const SDL_Scancode keyCode) const;
            bool isKeyReleased(const SDL_Scancode keyCode) const;

            // Returns true if the mouse button is pressed (0 = left, 1 = middle, 2 = right)
            bool isMouseButtonTriggered(int mouseButton) const;
            bool isMouseButtonPressed(int mouseButton) const;
            bool isMouseButtonReleased(int mouseButton) const;

            const Vector2& getMousePosition() const;
    };
}