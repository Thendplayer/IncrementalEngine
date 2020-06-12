#ifndef _TEXTURE_SHADER_H
#define _TEXTURE_SHADER_H

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>

namespace IncrementalEngine 
{
	class TextureShader
	{
	#define VERTEX_SHADER_PATH L"Shaders/texture.vs"
	#define PIXEL_SHADER_PATH L"Shaders/texture.ps"
	#define ALPHA_CUTOFF .5f

	public:
		TextureShader();
		virtual ~TextureShader();

		HRESULT Init(ID3D11Device* device, HWND hwnd);

		HRESULT Draw(
			ID3D11DeviceContext* deviceContext,
			int indexCount,
			ID3D11ShaderResourceView* texture
		);

	private:
		struct TextureBufferType
		{
			D3DXVECTOR4 cutoff;
		};

		ID3D11VertexShader* _vertexShader;
		ID3D11PixelShader* _pixelShader;
		ID3D11Buffer* _textureBuffer;
		ID3D11InputLayout* _layout;
		ID3D11SamplerState* _sampleState;

		HRESULT InitializeShader(
			ID3D11Device* device, 
			HWND hwnd, 
			WCHAR* vsFilename, 
			WCHAR* psFilename
		);

		HRESULT CompileShader(
			HWND hwnd, 
			ID3D10Blob*& buffer, 
			WCHAR* filename, 
			LPCSTR functionName, 
			LPCSTR profile
		);

		void OutputShaderErrorMessage(
			ID3D10Blob* errorMessage, 
			HWND hwnd, 
			WCHAR* shaderFilename
		);

		HRESULT SetShaderParameters(
			ID3D11DeviceContext* deviceContext,
			ID3D11ShaderResourceView* texture
		);
		
		void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);
	};
}

#endif