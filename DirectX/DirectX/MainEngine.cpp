#include <cassert>
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
		_renderingEngine(NULL),
		_renderWindow(NULL),
		_inputManager(NULL),
		//TODO: Uncomment
		//_soundEngine(NULL),
		_scene(NULL),
		_resources(NULL)
	{
	}

	Engine::~Engine()
	{
		if (ENGINE_INSTANCE == this)
		{
			ENGINE_INSTANCE = nullptr;
		}
	}

	void Engine::Run(EngineGame* game)
	{
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

		HRESULT result;

		_inputManager = new InputManager;
		_renderWindow = new RenderWindow;
		result = _inputManager->Init(_renderWindow);

		if (FAILED(result))
		{
			MessageBox(_renderWindow->GetHWND(), L"Could not initialize InputManager.", L"Error", MB_OK);
			return;
		}

		_renderingEngine = new RenderingEngine;
		result = _renderingEngine->Init(_renderWindow);

		if (FAILED(result))
		{
			MessageBox(_renderWindow->GetHWND(), L"Could not initialize RenderingEngine.", L"Error", MB_OK);
			return;
		}

		auto direct3D = _renderingEngine->GetDirect3DImplementation();
		_scene = new Scene(
			_renderWindow,
			_renderingEngine->GetShaderManager(),
			direct3D->GetDevice()
		);

		//TODO: Uncomment
		//_soundEngine = new SoundEngine;

		_resources = new Resources;
		result = _resources->Load();
	
		if (FAILED(result))
		{
			MessageBox(_renderWindow->GetHWND(), _resources->Error, L"Error", MB_OK);
			return;
		}
	}

	void Engine::Update(float dt)
	{
		_renderingEngine->Update(dt);
		_scene->Update();
	}

	void Engine::Draw()
	{
		_renderingEngine->Draw(_scene);
	}

    void Engine::DeInit()
    {
		CHECKED_DELETE(_resources);
		CHECKED_DELETE(_scene);
		//TODO: Uncomment
		//CHECKED_DELETE(_soundEngine);
		CHECKED_DELETE(_renderingEngine);
		CHECKED_DELETE(_renderWindow);
		CHECKED_DELETE(_inputManager);
    }

	bool Engine::IsOpen()
	{
        return true;
	}

	Scene* Engine::GetScene()
	{
		return _scene;
	}

	Resources* Engine::GetResources()
	{
		return _resources;
	}

	InputManager* Engine::GetInput()
	{
		return _inputManager;
	}
}