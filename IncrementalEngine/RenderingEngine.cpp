#include "RenderingEngine.h"
#include "Utils.h"
#include <cassert>

namespace IncrementalEngine
{
	RenderingEngine::RenderingEngine(Config config) :
		_direct3D(NULL),
		_camera(NULL),
		_shaderManager(NULL),
		_config(config)
	{
	}

	RenderingEngine::~RenderingEngine() 
	{
		CHECKED_DELETE(_direct3D);
		CHECKED_DELETE(_camera);
		CHECKED_DELETE(_shaderManager);
	}

	HRESULT RenderingEngine::Init(RenderWindow* renderWindow)
	{
		HRESULT result;
		
		_direct3D = new D3DImplementation(_config);
		if (!_direct3D)
		{
			return CO_E_ERRORINAPP;
		}

		result = _direct3D->Init(renderWindow);
		if (FAILED(result))
		{
			MessageBox(renderWindow->GetHWND(), L"Could not initialize Direct3D.", L"Error", MB_OK);
			return CO_E_ERRORINAPP;
		}

		UpdateWindow(renderWindow->GetHWND());

		_camera = new RenderCamera;
		if (!_camera)
		{
			return CO_E_ERRORINAPP;
		}

		_camera->SetPosition(DEFAULT_2D_CAMERA_POSITION);

		_shaderManager = new ShaderManager;
		if (!_shaderManager)
		{
			return CO_E_ERRORINAPP;
		}

		result = _shaderManager->Init(_direct3D, _camera, renderWindow->GetHWND());
		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		return S_OK;
	}

	void RenderingEngine::Update(float dt)
	{
	}
	
	HRESULT RenderingEngine::Draw(Drawable* target)
	{
		HRESULT result;

		_direct3D->BeginScene(
			_config.BackgroundColor.x / 255,
			_config.BackgroundColor.y / 255, 
			_config.BackgroundColor.z / 255, 
			_config.BackgroundColor.w
		);

		_camera->Draw();
		
		result = _shaderManager->SetupFrame();
		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		result = target->Draw(_direct3D->GetDeviceContext());
		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		_shaderManager->ClearFrame();
		_direct3D->EndScene();

		return S_OK;
	}
	
	D3DImplementation* RenderingEngine::GetDirect3DImplementation()
	{
		assert(_direct3D != nullptr, L"Direct3D must be initialized before call this method.");
		return _direct3D;
	}

	RenderCamera* RenderingEngine::GetCamera()
	{
		assert(_camera != nullptr, L"Camera must be initialized before call this method.");
		return _camera;
	}
	
	ShaderManager* RenderingEngine::GetShaderManager()
	{
		assert(_shaderManager != nullptr, L"ShaderManager must be initialized before call this method.");
		return _shaderManager;
	}
}