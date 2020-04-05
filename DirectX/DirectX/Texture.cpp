#include "Texture.h"
#include "Utils.h"

namespace MyEngine 
{
	Texture::Texture() :
		_texture(NULL)
	{
	}

	Texture::~Texture()
	{
		CHECKED_RELEASE(_texture);
	}

	HRESULT Texture::Init(ID3D11Device* device, WCHAR* filename)
	{
		HRESULT result = D3DX11CreateShaderResourceViewFromFile(
			device, 
			filename, 
			NULL, 
			NULL, 
			&_texture, 
			NULL
		);

		if (FAILED(result))
		{
			return FALSE;
		}

		return S_OK;
	}

	ID3D11ShaderResourceView* Texture::GetTexture()
	{
		return _texture;
	}
}