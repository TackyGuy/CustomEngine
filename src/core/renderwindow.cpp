#include "renderwindow.h"
using namespace Core;


SDL_Texture* RenderWindow::loadTexture(const char* filePath)
{
    SDL_Texture* texture = nullptr;
    texture = IMG_LoadTexture(_renderer, filePath);

    if (texture == nullptr) 
        std::cout << "Failed to load texture at '" << filePath << "'. Error: " << SDL_GetError() << std::endl;
    else std::cout << "Texture loaded succesfully..." << std::endl;

    return texture;
}

const int RenderWindow::getRefreshRate() const
{
    int displayIndex = SDL_GetWindowDisplayIndex(_window);
    
    SDL_DisplayMode mode;

    SDL_GetDisplayMode(displayIndex, 0, &mode);

    return mode.refresh_rate;
}

void RenderWindow::clear()
{
    SDL_RenderClear(_renderer);
}

void RenderWindow::renderTexture(SDL_Texture* texture, const SDL_Rect& src, const SDL_Rect& dst)
{
    if (texture != nullptr)
    {
        // std::cout << "Sprite: " << spriteRenderer->getSprite()->getPath() << ", texture: " << spriteRenderer->getSprite()->getTexture() << std::endl;
        if (SDL_RenderCopy(_renderer, texture, &src, &dst) != 0) std::cout << "[RenderWindow] SDL:" << SDL_GetError() << std::endl;
    }
}

SDL_Renderer *RenderWindow::getRenderer()
{
    return _renderer;
}

void RenderWindow::display()
{
    SDL_RenderPresent(_renderer);
}

void RenderWindow::prepareScene()
{
    std::cout << "Prepping scene..." << std::endl;

    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
}
