#include "bitmap.h"
#include "Utils.h"

namespace MyEngine 
{
	Bitmap::Bitmap() : 
		_vertexBuffer(NULL),
		_indexBuffer(NULL),
		_previousPosition(-1, -1),
		_previousScale(0, 0)
	{
	}

	Bitmap::~Bitmap()
	{
		CHECKED_RELEASE(_indexBuffer);
		CHECKED_RELEASE(_vertexBuffer);
	}

	HRESULT Bitmap::Create(Texture* texture)
	{
		HRESULT result;

		_previousPosition = D3DXVECTOR2(-1, -1);
		_previousScale = D3DXVECTOR2(0, 0);

		result = InitializeBuffers();
		if (FAILED(result))
		{
			MessageBox(_renderWindow->GetHWND(), L"Could not initialize Bitmap Buffers.", L"Error", MB_OK);
			return CO_E_ERRORINAPP;
		}

		result = texture->Init(_device);
		if (FAILED(result))
		{
			MessageBox(_renderWindow->GetHWND(), L"Could not load Bitmap Texture.", L"Error", MB_OK);
			return CO_E_ERRORINAPP;
		}

		_texture = texture;

		return S_OK;
	}

	HRESULT Bitmap::Draw(ID3D11DeviceContext* deviceContext)
	{
		HRESULT result;

		result = UpdateBuffers(deviceContext);
		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		RenderBuffers(deviceContext);

		result = _shaderManager->RenderTextureShader(_indexCount, _texture->GetTexture());
		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		return S_OK;
	}

	int Bitmap::GetIndexCount()
	{
		return _indexCount;
	}

	HRESULT Bitmap::InitializeBuffers()
	{
		VertexType* vertices;
		unsigned long* indices;
		D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
		D3D11_SUBRESOURCE_DATA vertexData, indexData;
		HRESULT result;

		_indexCount = _vertexCount = 6; //TODO: Move into a constant

		vertices = new VertexType[_vertexCount];
		if (!vertices)
		{
			return CO_E_ERRORINAPP;
		}

		indices = new unsigned long[_indexCount];
		if (!indices)
		{
			return CO_E_ERRORINAPP;
		}

		memset(vertices, 0, (sizeof(VertexType) * _vertexCount));

		for (int i = 0; i < _indexCount; i++)
		{
			indices[i] = i;
		}

		vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		vertexBufferDesc.ByteWidth = sizeof(VertexType) * _vertexCount;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.StructureByteStride = 0;

		vertexData.pSysMem = vertices;
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;

		result = _device->CreateBuffer(&vertexBufferDesc, &vertexData, &_vertexBuffer);
		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(unsigned long) * _indexCount;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;
		indexBufferDesc.StructureByteStride = 0;

		indexData.pSysMem = indices;
		indexData.SysMemPitch = 0;
		indexData.SysMemSlicePitch = 0;

		result = _device->CreateBuffer(&indexBufferDesc, &indexData, &_indexBuffer);
		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		delete[] vertices;
		vertices = 0;

		delete[] indices;
		indices = 0;

		return S_OK;
	}

	HRESULT Bitmap::UpdateBuffers(ID3D11DeviceContext* deviceContext)
	{
		if (_position == _previousPosition && _scale == _previousScale)
		{
			return S_OK;
		}

		float left, right, top, bottom;
		VertexType* vertices;
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		VertexType* verticesPtr;
		HRESULT result;

		_previousPosition = _position;
		_previousScale = _scale;

		left = (float)((_renderWindow->GetScreenWidth() / 2) * -1) + (float)_position.x;
		right = left + (float)GetScaledSize().x;
		
		top = (float)(_renderWindow->GetScreenHeight() / 2) - (float)_position.y;
		bottom = top - (float)GetScaledSize().y;

		vertices = new VertexType[_vertexCount];
		if (!vertices)
		{
			return CO_E_ERRORINAPP;
		}

		vertices[0].position = D3DXVECTOR3(left, top, 0.0f);  // Top left.
		vertices[0].texture = D3DXVECTOR2(0.0f, 0.0f);

		vertices[1].position = D3DXVECTOR3(right, bottom, 0.0f);  // Bottom right.
		vertices[1].texture = D3DXVECTOR2(1.0f, 1.0f);

		
		vertices[2].position = D3DXVECTOR3(left, bottom, 0.0f);  // Bottom left.
		vertices[2].texture = D3DXVECTOR2(0.0f, 1.0f);

		vertices[3].position = D3DXVECTOR3(left, top, 0.0f);  // Top left.
		vertices[3].texture = D3DXVECTOR2(0.0f, 0.0f);

		vertices[4].position = D3DXVECTOR3(right, top, 0.0f);  // Top right.
		vertices[4].texture = D3DXVECTOR2(1.0f, 0.0f);

		vertices[5].position = D3DXVECTOR3(right, bottom, 0.0f);  // Bottom right.
		vertices[5].texture = D3DXVECTOR2(1.0f, 1.0f);

		result = deviceContext->Map(_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		verticesPtr = (VertexType*)mappedResource.pData;
		memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType) * _vertexCount));

		deviceContext->Unmap(_vertexBuffer, 0);

		delete[] vertices;
		vertices = 0;

		return S_OK;
	}

	void Bitmap::RenderBuffers(ID3D11DeviceContext* deviceContext)
	{
		unsigned int stride = sizeof(VertexType);
		unsigned int offset = 0;

		deviceContext->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
		deviceContext->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
}