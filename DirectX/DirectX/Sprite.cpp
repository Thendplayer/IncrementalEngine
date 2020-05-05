#include "Sprite.h"
#include "Utils.h"

namespace MyEngine 
{
	Sprite::Sprite() :
		_texture(NULL)
	{
	}
	
	Sprite::~Sprite()
	{
		CHECKED_DELETE(_texture);
	}

	void Sprite::SetTexture(Texture* texture)
	{
		if (_texture != nullptr)
		{
			if (_texture->GetTexture() == texture)
			{
				return;
			}

			CHECKED_DELETE(_texture);
		}

		auto bitmap = new Bitmap;
		CopyParameters(bitmap);
		HRESULT result = bitmap->Create(texture);

		if (FAILED(result))
		{
			throw;
		}

		_texture = bitmap;
		Center();
	}

	void Sprite::ClearTexture()
	{
		CHECKED_DELETE(_texture);
	}

	FloatRect Sprite::GetLocalBounds()
	{
		FloatRect bounds = {
			0.f,
			0.f,
			_texture->GetSize().x,
			_texture->GetSize().y
		};

		return bounds;
	}
	
	void Sprite::Update()
	{
		_texture->Update(GetTransform(), GetLocalBounds());
	}
	
	HRESULT Sprite::Draw(ID3D11DeviceContext* deviceContext)
	{
		HRESULT result;

		if (_texture != nullptr)
		{
			result = _texture->Draw(deviceContext);

			if (FAILED(result))
			{
				return CO_E_ERRORINAPP;
			}
		}

		return S_OK;
	}
}