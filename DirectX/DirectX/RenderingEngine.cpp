#include "RenderingEngine.h"
#include "Utils.h"

namespace MyEngine
{
	RenderingEngine::RenderingEngine() :
		_direct3D(NULL),
		_camera(NULL),
		_textureShaderRenderer(NULL)
	{
	}

	RenderingEngine::~RenderingEngine() 
	{
		CHECKED_DELETE(_direct3D);
		CHECKED_DELETE(_camera);
		CHECKED_DELETE(_textureShaderRenderer);
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

		_textureShaderRenderer = new TextureShaderRenderer;
		if (!_textureShaderRenderer)
		{
			return FALSE;
		}

		result = _textureShaderRenderer->Initialize(_direct3D->GetDevice(), renderWindow->GetHWND());
		if (FAILED(result))
		{
			MessageBox(renderWindow->GetHWND(), L"Could not initialize the Texture Shader Renderer.", L"Error", MB_OK);
			return FALSE;
		}
	}
}