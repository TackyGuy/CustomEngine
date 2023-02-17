#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include "loader.hpp"
#include "renderwindow.hpp"
#include "audiomixer.hpp"
#include "actormanager.hpp"
#include "actor.hpp"
#include "basecomponent.hpp"
#include "transformcomponent.hpp"
#include "spriterenderercomponent.hpp"
#include "collision.hpp"
#include "collidercomponent.hpp"
#include "rigidbodycomponent.hpp"
#include "textcomponent.hpp"

#include "stage.hpp"
#include "stagemanager.hpp"
#include "menustage.hpp"
#include "sandboxstage.hpp"
#include "voltorbstage.hpp"

#include "utils.hpp"


using namespace Core;
using namespace Sandbox;

enum GameState {PLAY, QUIT};

class Game : public StageManager
{
    private:
        void init(const char* title, int x, int y);
        void update();
        void render();
        void handleCollisions();
        void handleEvents();
        Stage *m_stage = nullptr;
        bool m_loadingStage = false;
        bool m_start = false;

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

        void setStage(std::string stageName) override
        {
            if (m_loadingStage) return;
            if (!m_mixer) return;

            if (stageName == "menu") 
            {
                if (m_stage) delete m_stage;

                m_stage = new MenuStage(this, m_mixer);
            }
            else if (stageName == "voltorb") 
            {
                if (m_stage) delete m_stage;
                
                m_stage = new VoltorbFlip::VoltorbStage(this, m_mixer);
            }
            else if (stageName == "sandbox") 
            {
                if (m_stage) delete m_stage;
                
                m_stage = new Sandbox::SandboxStage(this, m_mixer);
            }
            else
            {
                std::cout << "Stage: " << stageName << " is invalid." << std::endl;
                return;
            }

            m_loadingStage = true;
            std::cout << "Loading stage '" << stageName << "'..." << std::endl;

            m_stage->preload();
            if (m_start) m_stage->start();
            m_loadingStage = false;
        }

        void run();
};