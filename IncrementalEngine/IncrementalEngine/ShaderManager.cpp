#include "ShaderManager.h"
#include <cassert>
#include "Utils.h"

namespace IncrementalEngine 
{
	ShaderManager::ShaderManager() :
		_textureShader(NULL),
		_matrixBuffer(NULL)
	{
	}

	ShaderManager::~ShaderManager()
	{
		CHECKED_DELETE(_textureShader);
		CHECKED_RELEASE(_matrixBuffer);
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

		result = InitGlobalBuffer();
		if (FAILED(result))
		{
			MessageBox(hWnd, L"Could not initialize the Global Buffer.", L"Error", MB_OK);
			return CO_E_ERRORINAPP;
		}

		return S_OK;
	}

	HRESULT ShaderManager::InitGlobalBuffer()
	{
		HRESULT result;
		D3D11_BUFFER_DESC matrixBufferDesc;

		matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
		matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		matrixBufferDesc.MiscFlags = 0;
		matrixBufferDesc.StructureByteStride = 0;

		result = _direct3D->GetDevice()->CreateBuffer(
			&matrixBufferDesc,
			NULL,
			&_matrixBuffer
		);

		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		return S_OK;
	}

	HRESULT ShaderManager::SetupFrame()
	{
		if (!_frameReady)
		{
			HRESULT result;
			D3DXMATRIX worldMatrix, viewMatrix, orthoProjectionMatrix;
			D3D11_MAPPED_SUBRESOURCE mappedResource;
			MatrixBufferType* dataPtr;

			_camera->GetViewMatrix(viewMatrix);
			_direct3D->GetWorldMatrix(worldMatrix);
			_direct3D->GetOrthoProjectionMatrix(orthoProjectionMatrix);

			D3DXMatrixTranspose(&worldMatrix, &worldMatrix);
			D3DXMatrixTranspose(&viewMatrix, &viewMatrix);
			D3DXMatrixTranspose(&orthoProjectionMatrix, &orthoProjectionMatrix);

			auto deviceContext = _direct3D->GetDeviceContext();
			result = deviceContext->Map(
				_matrixBuffer,
				0, //Buffer Index
				D3D11_MAP_WRITE_DISCARD,
				0,
				&mappedResource
			);

			if (FAILED(result))
			{
				return CO_E_ERRORINAPP;
			}

			dataPtr = (MatrixBufferType*)mappedResource.pData;

			dataPtr->world = worldMatrix;
			dataPtr->view = viewMatrix;
			dataPtr->projection = orthoProjectionMatrix;

			deviceContext->Unmap(_matrixBuffer, 0);
			deviceContext->VSSetConstantBuffers(0, 1, &_matrixBuffer);

			_frameReady = true;
		}

		return S_OK;
	}

	void ShaderManager::ClearFrame()
	{
		_frameReady = false;
	}

	HRESULT ShaderManager::RenderTextureShader(
		int indexCount,
		ID3D11ShaderResourceView* texture
	)
	{
		assert("SetupFrame() method has to be called before render a Shader." && _frameReady);
		HRESULT result;

		result = _textureShader->Draw(
			_direct3D->GetDeviceContext(),
			indexCount,
			texture
		);

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