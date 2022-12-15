#include "inputprovider.h"
using namespace Core;

void InputProvider::initialize()
{
    // Initialize the previous input array
    // memset(m_pPreviousInput, 0, sizeof(Uint8) * SDL_NUM_SCANCODES);
    // Copy the Keyboard state
    _currentInput = const_cast<Uint8*>(SDL_GetKeyboardState(NULL));
}
void InputProvider::handleInputs()
{
    SDL_PumpEvents();

    handleKeyboard();
    handleMouse();
}
void InputProvider::handleKeyboard()
{
    // Copy the current inputs into the previous inputs
    _previousInput = _currentInput;
    // Copy the GetKeyboardState into the current inputs
    _currentInput = const_cast<Uint8*>(SDL_GetKeyboardState(NULL));
}
void InputProvider::handleMouse()
{
    int mouseX, mouseY;
    m_mouseState = SDL_GetMouseState(&mouseX, &mouseY);

    m_mousePos.set(mouseX, mouseY);

    handleEventsUI();
}
void InputProvider::handleEventsUI()
{
    BoundingBox mouseBox = BoundingBox(m_mousePos, Vector2(1, 1));
    auto touchedElement = UIManager::checkOverlapWithUI(mouseBox);
    // std::cout << &*touchedElement << std::endl;

    if (touchedElement)
    {
        if (isMouseButtonPressed(0)) touchedElement->onClick();
        else if (touchedElement != _currentHovered) touchedElement->onHoverBegin();
        else touchedElement->onHover();
    }

    if (_currentHovered != touchedElement) 
    {
        if (_currentHovered) _currentHovered->onHoverEnd();
    }

    _currentHovered = touchedElement;
}

bool InputProvider::isKeyTriggered(const SDL_Scancode keyCode) const
{
    return (_currentInput[keyCode] == 1 && _previousInput[keyCode] == 0);
}
bool InputProvider::isKeyPressed(const SDL_Scancode keyCode) const
{
    return (_currentInput[keyCode] == 1);
}
bool InputProvider::isKeyReleased(const SDL_Scancode keyCode) const
{
    return (_currentInput[keyCode] == 0 && _previousInput[keyCode] == 1);
}

bool InputProvider::isMouseButtonPressed(int mouseButton) const
{
    switch (mouseButton)
    {
        case 0:
            if ((m_mouseState & SDL_BUTTON_LMASK) != 0) return true;
            break;
        case 1:
            if ((m_mouseState & SDL_BUTTON_MMASK) != 0) return true;
            break;
        case 2:
            if ((m_mouseState & SDL_BUTTON_RMASK) != 0) return true;
            break;
        
        default:
            return false;
            break;
    }

    return false;
}
bool InputProvider::isMouseButtonReleased(int mouseButton) const
{
    return false;
}