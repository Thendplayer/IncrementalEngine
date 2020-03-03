#include <cassert>
#include <chrono>
#include <thread>

#include "MainEngine.h"
#include "EngineGame.h"
#include "Utils.h"

namespace MyEngine
{
	#define FPS 60
	#define DELTA_SECONDS (1.0 / FPS)
	
	Engine* Engine::ENGINE_INSTANCE = nullptr;

	Engine* Engine::Get()
	{
		if (ENGINE_INSTANCE == nullptr)
		{
			ENGINE_INSTANCE = new Engine;
		}

		return ENGINE_INSTANCE;
	}

	Engine::Engine() :
	renderingEngine(NULL),
	inputManager(NULL),
	hInstance(NULL)
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

        MSG msg;
        ZeroMemory(&msg, sizeof(msg));
		
        while (msg.message != WM_QUIT)
        {
			if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				Update(float(DELTA_SECONDS));
				game->Update(float(DELTA_SECONDS));
				
				Draw();
			}
        }

        game->DeInit();
        DeInit();
	}

	void Engine::Init()
	{
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

        renderingEngine = new RenderingEngine(hInstance);
		auto hWnd = renderingEngine->Init();

		inputManager = new InputManager(hWnd);
	}

	void Engine::Update(float dt)
	{
	}

	void Engine::Draw()
	{
	}

    void Engine::DeInit()
    {
		delete renderingEngine;
		CHECKED_DELETE(renderingEngine);
    }

	bool Engine::IsOpen()
	{
        return true;
	}
}
