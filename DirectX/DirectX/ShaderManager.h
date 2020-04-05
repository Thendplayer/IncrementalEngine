#ifndef _SHADER_MANAGER_H
#define _SHADER_MANAGER_H

#include <D3DX11.h>
#include "D3DImplementation.h"
#include "RenderCamera.h"
#include "TextureShader.h"

namespace MyEngine
{
	class ShaderManager
	{
	public:
		HRESULT Init(D3DImplementation* direct3D, RenderCamera* camera, HWND hWnd);

		HRESULT RenderTextureShader(
			int indexCount, 
			ID3D11ShaderResourceView* texture
		);

		ShaderManager();
		~ShaderManager();

	private:
		D3DImplementation* _direct3D;
		RenderCamera* _camera;
		TextureShader* _textureShader;
	};
}

#endif