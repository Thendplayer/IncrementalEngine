#include "RenderingEngine.h"
#include "Utils.h"
#include <cassert>

namespace MyEngine
{
	RenderingEngine::RenderingEngine() :
		_direct3D(NULL),
		_camera(NULL),
		_shaderManager(NULL)
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
		
		_direct3D = new D3DImplementation;
		if (!_direct3D)
		{
			return FALSE;
		}

		result = _direct3D->Init(renderWindow);
		if (FAILED(result))
		{
			MessageBox(renderWindow->GetHWND(), L"Could not initialize Direct3D.", L"Error", MB_OK);
			return FALSE;
		}

		UpdateWindow(renderWindow->GetHWND());

		_camera = new RenderCamera;
		if (!_camera)
		{
			return FALSE;
		}

		_camera->SetPosition(DEFAULT_2D_CAMERA_POSITION);

		_shaderManager = new ShaderManager;
		if (!_shaderManager)
		{
			return FALSE;
		}

		result = _shaderManager->Init(_direct3D, _camera, renderWindow->GetHWND());
		if (FAILED(result))
		{
			return FALSE;
		}

		return S_OK;
	}

	void RenderingEngine::Update(float dt)
	{
	}
	
	HRESULT RenderingEngine::Draw(Drawable* target)
	{
		HRESULT result;

		_direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
		_camera->Draw();

		result = target->Draw(_direct3D->GetDeviceContext());
		if (FAILED(result))
		{
			return FALSE;
		}

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