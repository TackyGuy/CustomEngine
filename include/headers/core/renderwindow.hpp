#pragma once

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

#include "mathutils.hpp"

namespace Core
{
    class RenderWindow
    {
        private:
            SDL_Window* _window = nullptr;
            SDL_Renderer* _renderer = nullptr;

            void prepareScene();
        public:
            ~RenderWindow()
            {
                SDL_DestroyRenderer(_renderer);
                SDL_DestroyWindow(_window);
            }
            RenderWindow(){};
            
            RenderWindow(const char* title, int x, int y, int width, int height)
            {
                _window = SDL_CreateWindow(title, x, y, width, height, SDL_WINDOW_SHOWN);
                if (_window == NULL) std::cout << "Window failed to initialize. Error: " << SDL_GetError() << std::endl;
                _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

                prepareScene();
            }

            SDL_Texture *loadTexture(const char* filePath);

            const int getRefreshRate() const;

            void cleanUp();
            void clear();
            void renderTexture(SDL_Texture* texture, const SDL_Rect& src, const SDL_Rect& dst);
            SDL_Renderer *getRenderer();
            void display();
    };
}