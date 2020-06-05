#include <cassert>
#include <thread>

#include "MainEngine.h"
#include "EngineGame.h"

namespace IncrementalEngine
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
		_soundEngine(NULL),
		_sceneManager(NULL),
		_resourcesManager(NULL),
		_saveSystem(NULL),
		_config(Config())
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
		_renderWindow = new RenderWindow(_config);
		result = _inputManager->Init(_renderWindow);

		if (FAILED(result))
		{
			MessageBox(_renderWindow->GetHWND(), L"Could not initialize InputManager.", L"Error", MB_OK);
			return;
		}

		_renderingEngine = new RenderingEngine(_config);
		result = _renderingEngine->Init(_renderWindow);

		if (FAILED(result))
		{
			MessageBox(_renderWindow->GetHWND(), L"Could not initialize RenderingEngine.", L"Error", MB_OK);
			return;
		}

		auto direct3D = _renderingEngine->GetDirect3DImplementation();
		_sceneManager = new SceneManager(
			_renderWindow,
			_renderingEngine->GetShaderManager(),
			direct3D->GetDevice()
		);

		_soundEngine = new SoundEngine;

		_resourcesManager = new ResourcesManager;
		result = _resourcesManager->Load();

		_saveSystem = new SaveSystem;
	
		if (FAILED(result))
		{
			MessageBox(_renderWindow->GetHWND(), _resourcesManager->Error, L"Error", MB_OK);
			return;
		}
	}

	void Engine::Update(float dt)
	{
		_renderingEngine->Update(dt);
		_inputManager->Update();
		_sceneManager->Update(dt);
	}

	void Engine::Draw()
	{
		_renderingEngine->Draw(_sceneManager);
	}

    void Engine::DeInit()
    {
		FontFactory::Release();

		CHECKED_DELETE(_saveSystem);
		CHECKED_DELETE(_resourcesManager);
		CHECKED_DELETE(_sceneManager);
		CHECKED_DELETE(_soundEngine);
		CHECKED_DELETE(_renderingEngine);
		CHECKED_DELETE(_renderWindow);
		CHECKED_DELETE(_inputManager);
    }

	bool Engine::IsOpen()
	{
        return true;
	}

	SceneManager* Engine::Scene()
	{
		return _sceneManager;
	}

	ResourcesManager* Engine::Resources()
	{
		return _resourcesManager;
	}

	SoundEngine* Engine::Audio()
	{
		return _soundEngine;
	}

	InputManager* Engine::Input()
	{
		return _inputManager;
	}
	
	SaveSystem* Engine::Storage()
	{
		return _saveSystem;
	}
}