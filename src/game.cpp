#include "game.h"

using namespace Core;

Game::Game()
{
    m_GameState = GameState::PLAY;
}

Game::~Game()
{
    std::cout << "destroying game and cleaning up..." << std::endl;
    
    delete m_stage;
    m_window.reset();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}

void Game::run()
{
    init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    update();
}

bool Game::isInBounds(TransformComponent *trans)
{
    float x = trans->getPosition().getX();
    float y = trans->getPosition().getY();

    if (x < 0 || x > SCREEN_WIDTH)
        return false;
    if (y < 0 || y > SCREEN_HEIGHT)
        return false;

    return true;
}

void Game::init(const char* title, int x, int y)
{
    if (SDL_Init(SDL_INIT_EVERYTHING))
        std::cout << "SDL_Init FAILED. ERROR: " << SDL_GetError() << std::endl;

    if (!IMG_Init(IMG_INIT_PNG))
        std::cout << "IMG_Init FAILED. ERROR: " << SDL_GetError() << std::endl;
    
    if (TTF_Init() == -1)
        std::cout << "TTF_Init FAILED. ERROR: " << TTF_GetError() << std::endl;

    Mix_Init(MIX_INIT_MP3);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        std::cout << "Mix_Init FAILED. ERROR: " << Mix_GetError() << std::endl;

    
    m_window = std::make_shared<RenderWindow>(title, x, y, SCREEN_WIDTH, SCREEN_HEIGHT);
    windowRefreshRate = m_window->getRefreshRate();

    Loader::init(*m_window);

    m_mixer = std::make_shared<AudioMixer>(AudioMixer(0.5));

    // m_stage = new SandboxStage(m_mixer);
    m_stage = new Demo1::VoltorbStage(m_mixer);
    m_stage->preload();
}

void Game::update()
{
    m_stage->init();
    while (m_GameState != GameState::QUIT)
    {
        // Current time
        float newtime = utils::elapsedTimeInSeconds();
        // time it took to complete the last frame
        double frameTime = newtime - m_lastFrameTime;
        // We assign the new time to a buffer
        m_lastFrameTime = newtime;
        
        m_accumulator += frameTime;

        while (m_accumulator >= fixedTime)
        {
            // Check collisions
            handleCollisions();
            // Handle events
            handleEvents();
            // TODO FixedUpdate here
            // find out why it crashes
            m_stage->update(fixedTime);
            
            m_accumulator -= fixedTime;
            m_currentTime += fixedTime;
        }
        
        render();
        // We delay the update
        /*int frameTicks = SDL_GetTicks() - startTicks;

        if (frameTicks < (1000 /windowRefreshRate))
        {
            SDL_Delay((1000 /windowRefreshRate) - frameTicks);
        }*/
    }
    
}

void Game::render()
{
    m_window->clear();

    for (std::weak_ptr<Actor> weakPtr : ActorManager::s_actors)
    {
        auto actor = weakPtr.lock();
        if (actor) actor->render(m_window.get());
        
    }
    m_window->display();
}

void Game::handleCollisions()
{
    for (std::weak_ptr<Actor> weakPtr : ActorManager::s_actors)
    {
        auto actor = weakPtr.lock();
        if (!actor) return;

        auto rb = actor->getComponent<RigidbodyComponent>();
        if (!rb) continue;

        if (!Collision::bspDone)
        {
            auto col = rb->getCollider();
            if (col == nullptr) continue;

            if (!Collision::findCollider(actor->getID())) Collision::addCollider(actor->getID(), col);
        }
        else
        {
            if (rb->bodyType == RigidbodyComponent::Body::DYNAMIC)
            {
                if (rb->getCollider()) continue;
                
                auto cols = Collision::getColliders(rb->getCollider());
                if (cols.size())
                {
                    for (auto col : cols)
                    {
                        rb->onCollision(col);
                    }
                }
            }
        }

        
    }

    if (!Collision::bspDone) Collision::createNodeTree();
}

void Game::handleEvents()
{
    SDL_Event event;

    while(SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT) m_GameState = GameState::QUIT;
    }

    m_stage->getInputProvider()->handleInputs();
}
