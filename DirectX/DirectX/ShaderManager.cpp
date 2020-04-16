#include "ShaderManager.h"
#include "Utils.h"

namespace MyEngine 
{
	ShaderManager::ShaderManager() :
		_textureShader(NULL)
	{
	}

	ShaderManager::~ShaderManager()
	{
		CHECKED_DELETE(_textureShader);
	}

	HRESULT ShaderManager::Init(D3DImplementation* direct3D, RenderCamera* camera, HWND hWnd)
	{
		HRESULT result;

		_direct3D = direct3D;
		_camera = camera;

		_textureShader = new TextureShader;
		if (!_textureShader)
		{
			return CO_E_ERRORINAPP;
		}

		result = _textureShader->Init(_direct3D->GetDevice(), hWnd);
		if (FAILED(result))
		{
			MessageBox(hWnd, L"Could not initialize the Texture Shader Renderer.", L"Error", MB_OK);
			return CO_E_ERRORINAPP;
		}

		return S_OK;
	}

	HRESULT ShaderManager::RenderTextureShader(
		int indexCount,
		ID3D11ShaderResourceView* texture
	)
	{
		HRESULT result;
		D3DXMATRIX worldMatrix, viewMatrix, orthoProjectionMatrix;

		_camera->GetViewMatrix(viewMatrix);
		_direct3D->GetWorldMatrix(worldMatrix);
		_direct3D->GetOrthoProjectionMatrix(orthoProjectionMatrix);

		_direct3D->TurnZBufferOff();

		result = _textureShader->Draw(
			_direct3D->GetDeviceContext(),
			indexCount,
			worldMatrix,
			viewMatrix,
			orthoProjectionMatrix,
			texture
		);

		_direct3D->TurnZBufferOn();

		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		return S_OK;
	}
	
	void ShaderManager::SetWorldMatrix(D3DXMATRIX& worldMatrix)
	{
		_direct3D->SetWorldMatrix(worldMatrix);
	}
}