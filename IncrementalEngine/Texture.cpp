#include "Texture.h"
#include "Utils.h"

namespace IncrementalEngine 
{
	Texture::Texture(std::string filename) :
		_texture(NULL),
		_size(0, 0),
		_filename(filename)
	{
	}

	Texture::~Texture()
	{
		CHECKED_RELEASE(_texture);
	}

	HRESULT Texture::Init(ID3D11Device* device)
	{
		ID3D11Resource* resource;
		ID3D11Texture2D* texture2D;
		D3D11_TEXTURE2D_DESC desc;

		std::wstring filename(_filename.begin(), _filename.end());
		HRESULT result = D3DX11CreateShaderResourceViewFromFile(
			device, 
			filename.c_str(),
			NULL, 
			NULL, 
			&_texture, 
			NULL
		);

		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		_texture->GetResource(&resource);
		texture2D = static_cast<ID3D11Texture2D*>(resource);

		if (texture2D == nullptr)
		{
			return CO_E_ERRORINAPP;
		}

		texture2D->GetDesc(&desc);
		_size = D3DXVECTOR2(desc.Width, desc.Height);

		return S_OK;
	}

	ID3D11ShaderResourceView* Texture::GetTexture()
	{
		return _texture;
	}
	
	D3DXVECTOR2 Texture::GetSize()
	{
		return _size;
	}
}