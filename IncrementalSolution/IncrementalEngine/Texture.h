#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <d3d11.h>
#include <d3dx11tex.h>
#include <D3DX10.h>

#include <string>

namespace IncrementalEngine 
{
	class Texture
	{
	public:
		HRESULT Init(ID3D11Device* device);
		
		ID3D11ShaderResourceView* GetTexture();
		D3DXVECTOR2 GetSize();

		Texture(std::string filename);
		virtual ~Texture();

	private:
		ID3D11ShaderResourceView* _texture;
		std::string _filename;
		D3DXVECTOR2 _size;
	};
}

#endif