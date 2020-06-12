#ifndef _SHADER_MANAGER_H
#define _SHADER_MANAGER_H

#include <D3DX11.h>
#include "D3DImplementation.h"
#include "RenderCamera.h"
#include "TextureShader.h"

namespace IncrementalEngine
{
	class ShaderManager
	{
	public:
		HRESULT Init(D3DImplementation* direct3D, RenderCamera* camera, HWND hWnd);

		HRESULT RenderTextureShader(
			int indexCount, 
			ID3D11ShaderResourceView* texture
		);

		HRESULT SetupFrame();
		void ClearFrame();

		void SetWorldMatrix(D3DXMATRIX& worldMatrix);

		ShaderManager();
		virtual ~ShaderManager();

	private:
		struct MatrixBufferType
		{
			D3DXMATRIX world;
			D3DXMATRIX view;
			D3DXMATRIX projection;
		};

		D3DImplementation* _direct3D;
		RenderCamera* _camera;
		TextureShader* _textureShader;
		ID3D11Buffer* _matrixBuffer;

		bool _frameReady;

		HRESULT InitGlobalBuffer();
	};
}

#endif