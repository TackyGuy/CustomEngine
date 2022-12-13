#pragma once

#include "SDL.h"
#include <string.h>
#include <iostream>

#include "math.h"
#include "userinterface.h"

namespace Core
{
    class InputProvider
    {
        private:
            Uint8 *_previousInput = nullptr;
            Uint8 *_currentInput = nullptr;

            Uint32 m_mouseState;
            Vector2 m_mousePos;

            UserInterface  *_currentHovered = nullptr;
            
        public:
            ~InputProvider(){}
            InputProvider()
            {}

            void initialize();
            void handleInputs();
            void handleKeyboard();
            void handleMouse();
            void handleEventsUI();

            bool isKeyTriggered(const SDL_Scancode keyCode) const;
            bool isKeyPressed(const SDL_Scancode keyCode) const;
            bool isKeyReleased(const SDL_Scancode keyCode) const;

            // Returns true if the mouse button is pressed (0 = left, 1 = middle, 2 = right)
            bool isMouseButtonPressed(int mouseButton) const;
            bool isMouseButtonReleased(int mouseButton) const;
    };
}