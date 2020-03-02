#include "MainEngine.h"
#include "EngineGame.h"
#include <cassert>
#include <chrono>
#include <thread>

namespace MyEngine
{
	Engine* Engine::ENGINE_INSTANCE = nullptr;

	const int FPS = 60;
    const double DELTA_SECONDS = 1.0 / FPS;

    const double MAX_TIME_DIFF = 5.0;
    const int MAX_SKIPPED_FRAMES = 5;
	
	Engine* Engine::Get()
	{
		if (ENGINE_INSTANCE == nullptr)
		{
			ENGINE_INSTANCE = new Engine;
		}

		return ENGINE_INSTANCE;
	}

	Engine::Engine()
	{
	}

	Engine::~Engine()
	{
		ENGINE_INSTANCE = nullptr;
	}

	void Engine::Run(HINSTANCE hInstance, EngineGame* game)
	{
        this->hInstance = hInstance;
		
        Init();
        game->Init();

        auto initialTime = std::chrono::system_clock::now();
        auto skippedFrames = 1;
		auto nextTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - initialTime).count() / 1000.0;

        while (IsOpen())
        {
            auto currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - initialTime).count() / 1000.0;

            if (currentTime - nextTime > MAX_TIME_DIFF)
            {
                nextTime = currentTime;
            }

            if (currentTime >= nextTime)
            {
                nextTime += DELTA_SECONDS;

                Update((float)DELTA_SECONDS);
                game->Update((float)DELTA_SECONDS);
            	
                if (currentTime < nextTime || skippedFrames > MAX_SKIPPED_FRAMES)
                {
                    Draw();
                    skippedFrames = 1;
                }
                else
                {
                    skippedFrames++;
                }
            }
            else
            {
	            auto sleepTime = (int)(1000.0 * (nextTime - currentTime));
                if (sleepTime > 0)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
                }
            }
        }

        game->DeInit();
        DeInit();
	}

	void Engine::Init()
	{
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

        renderingEngine = new RenderingEngine(hInstance);
	}

	void Engine::Update(float dt)
	{
	}

	void Engine::Draw()
	{
	}

    void Engine::DeInit()
    {
    }

	bool Engine::IsOpen()
	{
        return true;
	}
}
