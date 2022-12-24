#pragma once


#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "loader.h"
#include "renderwindow.h"
#include "audiomixer.h"
#include "actormanager.h"
#include "actor.h"
#include "basecomponent.h"
#include "transformcomponent.h"
#include "spriterenderercomponent.h"
#include "collision.h"
#include "collidercomponent.h"
#include "rigidbodycomponent.h"
#include "textcomponent.h"

#include "stage.h"
#include "sandboxstage.h"
#include "voltorbstage.h"

#include "utils.h"

#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace Core;
using namespace Sandbox;

enum GameState {PLAY, QUIT};

class Game
{

    private:
        void init(const char* title, int x, int y);
        void update();
        void render();
        void handleCollisions();
        void handleEvents();
        Stage *m_stage = nullptr;

        std::shared_ptr<RenderWindow> m_window;
        std::shared_ptr<AudioMixer> m_mixer = nullptr;
        int windowRefreshRate;
        GameState m_GameState;

        double m_currentTime = 0.0f;
        const double fixedTime = 0.01f;

        double m_lastFrameTime = utils::elapsedTimeInSeconds();
        double m_accumulator = 0.0f;

    public: 
        Game();
        ~Game();

        inline static const int SCREEN_WIDTH = 1024;
        inline static const int SCREEN_HEIGHT = 720;

        void run();

        bool isInBounds(TransformComponent *trans);
};