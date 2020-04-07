#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <d3d11.h>
#include <d3dx11tex.h>
#include <D3DX10.h>

namespace MyEngine 
{
	class Texture
	{
	public:
		HRESULT Init(ID3D11Device* device, WCHAR* filename);
		ID3D11ShaderResourceView* GetTexture();

		Texture();
		~Texture();

	private:
		ID3D11ShaderResourceView* _texture;
		D3DXVECTOR2 _size;
	};
}

#endif