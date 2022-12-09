#include "renderwindow.h"
using namespace Core;


RenderWindow::RenderWindow(const char* title, int x, int y, int width, int height):_window(NULL), _renderer(NULL)
{
    _window = SDL_CreateWindow(title, x, y, width, height, SDL_WINDOW_SHOWN);
    if (_window == NULL) std::cout << "Window failed to initialize. Error: " << SDL_GetError() << std::endl;
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    prepareScene();
}

SDL_Texture* RenderWindow::loadTexture(const char* filePath)
{
    SDL_Texture* texture = nullptr;
    texture = IMG_LoadTexture(_renderer, filePath);

    if (texture == nullptr) 
        std::cout << "Failed to load texture at '" << filePath << "'. Error: " << SDL_GetError() << std::endl;
    else std::cout << "Texture loaded succesfully..." << std::endl;

    return texture;
}

int RenderWindow::getRefreshRate()
{
    int displayIndex = SDL_GetWindowDisplayIndex(_window);
    
    SDL_DisplayMode mode;

    SDL_GetDisplayMode(displayIndex, 0, &mode);

    return mode.refresh_rate;
}

void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(_window);
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
