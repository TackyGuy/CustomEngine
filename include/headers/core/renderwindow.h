#pragma once

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

#include "math.h"

namespace Core
{
    class RenderWindow
    {
        public:
            RenderWindow()
            {}
            RenderWindow(const char* title, int x, int y, int width, int height);

            SDL_Texture* loadTexture(const char* filePath);

            int getRefreshRate();

            void cleanUp();
            void clear();
            void renderTexture(SDL_Texture* texture, const SDL_Rect& src, const SDL_Rect& dst);
            SDL_Renderer *getRenderer();
            void display();
        private:
            SDL_Window* _window;
            SDL_Renderer* _renderer;

            void prepareScene();
            
    };
}