#include "TextureShader.h"
#include "Utils.h"

namespace MyEngine
{
	TextureShader::TextureShader() :
		_vertexShader(NULL),
		_pixelShader(NULL),
		_textureBuffer(NULL),
		_layout(NULL),
		_sampleState(NULL)
	{
	}

	TextureShader::~TextureShader()
	{
		CHECKED_RELEASE(_sampleState);
		CHECKED_RELEASE(_layout);
		CHECKED_RELEASE(_textureBuffer);
		CHECKED_RELEASE(_pixelShader);
		CHECKED_RELEASE(_vertexShader);
	}

	HRESULT TextureShader::Init(ID3D11Device* device, HWND hwnd)
	{
		HRESULT result;

		result = InitializeShader(
			device,
			hwnd,
			(WCHAR*)VERTEX_SHADER_PATH,
			(WCHAR*)PIXEL_SHADER_PATH
		);

		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		return S_OK;
	}

	HRESULT TextureShader::Draw(
		ID3D11DeviceContext* deviceContext,
		int indexCount,
		ID3D11ShaderResourceView* texture
	)
	{
		HRESULT result;

		result = SetShaderParameters(
			deviceContext, 
			texture
		);

		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		RenderShader(deviceContext, indexCount);

		return S_OK;
	}

	HRESULT TextureShader::InitializeShader(
		ID3D11Device* device, 
		HWND hwnd, 
		WCHAR* vsFilename, 
		WCHAR* psFilename
	)
	{
		HRESULT result;
		ID3D10Blob* vertexShaderBuffer = NULL;
		ID3D10Blob* pixelShaderBuffer = NULL;

		D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
		D3D11_BUFFER_DESC textureBufferDesc;
		unsigned int numElements;
		D3D11_SAMPLER_DESC samplerDesc;

		result = CompileShader(
			hwnd, 
			vertexShaderBuffer, 
			vsFilename, 
			"TextureVertexShader", 
			"vs_5_0"
		);

		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		result = CompileShader(
			hwnd,
			pixelShaderBuffer,
			psFilename, 
			"TexturePixelShader", 
			"ps_5_0"
		);

		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		result = device->CreateVertexShader(
			vertexShaderBuffer->GetBufferPointer(), 
			vertexShaderBuffer->GetBufferSize(), 
			NULL, 
			&_vertexShader
		);

		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		result = device->CreatePixelShader(
			pixelShaderBuffer->GetBufferPointer(), 
			pixelShaderBuffer->GetBufferSize(), 
			NULL, 
			&_pixelShader
		);

		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		polygonLayout[0].SemanticName = "POSITION";
		polygonLayout[0].SemanticIndex = 0;
		polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		polygonLayout[0].InputSlot = 0;
		polygonLayout[0].AlignedByteOffset = 0;
		polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		polygonLayout[0].InstanceDataStepRate = 0;

		polygonLayout[1].SemanticName = "TEXCOORD";
		polygonLayout[1].SemanticIndex = 0;
		polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
		polygonLayout[1].InputSlot = 0;
		polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		polygonLayout[1].InstanceDataStepRate = 0;

		numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

		result = device->CreateInputLayout(
			polygonLayout, 
			numElements, 
			vertexShaderBuffer->GetBufferPointer(), 
			vertexShaderBuffer->GetBufferSize(),
			&_layout
		);

		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		CHECKED_RELEASE(vertexShaderBuffer);
		CHECKED_RELEASE(pixelShaderBuffer);


		textureBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		textureBufferDesc.ByteWidth = sizeof(TextureBufferType);
		textureBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		textureBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		textureBufferDesc.MiscFlags = 0;
		textureBufferDesc.StructureByteStride = 0;

		result = device->CreateBuffer(
			&textureBufferDesc,
			NULL,
			&_textureBuffer
		);

		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MaxAnisotropy = 1;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		samplerDesc.BorderColor[0] = 0;
		samplerDesc.BorderColor[1] = 0;
		samplerDesc.BorderColor[2] = 0;
		samplerDesc.BorderColor[3] = 0;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

		result = device->CreateSamplerState(
			&samplerDesc, 
			&_sampleState
		);

		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		return S_OK;
	}

	HRESULT TextureShader::CompileShader(
		HWND hwnd,
		ID3D10Blob*& buffer,
		WCHAR* filename, 
		LPCSTR functionName, 
		LPCSTR profile
	)
	{
		ID3D10Blob* errorMessage = NULL;

		HRESULT result = D3DX11CompileFromFile(
			filename,
			NULL,
			NULL,
			functionName,
			profile,
			D3D10_SHADER_ENABLE_STRICTNESS,
			0,
			NULL,
			&buffer,
			&errorMessage,
			NULL
		);

		if (FAILED(result))
		{
			if (errorMessage)
			{
				OutputShaderErrorMessage(errorMessage, hwnd, filename);
			}
			else
			{
				MessageBox(hwnd, filename, L"Missing Shader File", MB_OK);
			}

			return CO_E_ERRORINAPP;
		}

		return S_OK;
	}

	void TextureShader::OutputShaderErrorMessage(
		ID3D10Blob* errorMessage, 
		HWND hwnd, 
		WCHAR* shaderFilename
	)
	{
		ofstream fout;
		
		char* compileErrors = (char*)(errorMessage->GetBufferPointer());
		unsigned long bufferSize = errorMessage->GetBufferSize();

		fout.open("shader-error.txt");

		for (int i = 0; i < bufferSize; i++)
		{
			fout << compileErrors[i];
		}

		fout.close();

		CHECKED_RELEASE(errorMessage);
		MessageBox(hwnd, L"Error compiling shader. Check shader-error.txt for message.", shaderFilename, MB_OK);
	}

	HRESULT TextureShader::SetShaderParameters(
		ID3D11DeviceContext* deviceContext, 
		ID3D11ShaderResourceView* texture
	)
	{
		HRESULT result;
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		TextureBufferType* dataPtr;
		
		result = deviceContext->Map(
			_textureBuffer, 
			0, 
			D3D11_MAP_WRITE_DISCARD, 
			0, 
			&mappedResource
		);

		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		dataPtr = (TextureBufferType*)mappedResource.pData;
		dataPtr->cutoff = D3DXVECTOR4(.0f, .0f, .0f, ALPHA_CUTOFF);

		deviceContext->Unmap(_textureBuffer, 1);

		deviceContext->PSSetConstantBuffers(1, 1, &_textureBuffer);
		deviceContext->PSSetShaderResources(0, 1, &texture);
	}

	void TextureShader::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
	{
		deviceContext->IASetInputLayout(_layout);

		deviceContext->VSSetShader(_vertexShader, NULL, 0);
		deviceContext->PSSetShader(_pixelShader, NULL, 0);

		deviceContext->PSSetSamplers(0, 1, &_sampleState);

		deviceContext->DrawIndexed(indexCount, 0, 0);
	}
}