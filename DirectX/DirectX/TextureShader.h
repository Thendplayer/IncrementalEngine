#ifndef _TEXTURE_SHADER_H
#define _TEXTURE_SHADER_H

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>

using namespace std;

namespace MyEngine 
{
	class TextureShader
	{
	public:
		TextureShader();
		~TextureShader();

		HRESULT Init(ID3D11Device* device, HWND hwnd);

		HRESULT Draw(
			ID3D11DeviceContext* deviceContext,
			int indexCount,
			D3DXMATRIX worldMatrix,
			D3DXMATRIX viewMatrix,
			D3DXMATRIX projectionMatrix,
			ID3D11ShaderResourceView* texture
		);

	private:
		struct MatrixBufferType
		{
			D3DXMATRIX world;
			D3DXMATRIX view;
			D3DXMATRIX projection;
		};

		ID3D11VertexShader* _vertexShader;
		ID3D11PixelShader* _pixelShader;
		ID3D11InputLayout* _layout;
		ID3D11Buffer* _matrixBuffer;
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
			D3DXMATRIX worldMatrix,
			D3DXMATRIX viewMatrix,
			D3DXMATRIX projectionMatrix,
			ID3D11ShaderResourceView* texture
		);
		
		void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);
	};
}

#endif