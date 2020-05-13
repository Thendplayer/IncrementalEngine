#include "TextureBase.h"

namespace IncrementalEngine 
{
	TextureBase::TextureBase() :
		_texture(NULL)
	{
		_transform = Transform();
		_bounds = { 0, 0, 0, 0 };
	}

	TextureBase::~TextureBase()
	{
	}

	void TextureBase::Update(Transform transform, FloatRect bounds)
	{
		_transform = transform;
		_bounds = bounds;
	}

	Texture* TextureBase::GetTexture()
	{
		return _texture;
	}
	
	D3DXVECTOR2 TextureBase::GetSize()
	{
		return _texture->GetSize();
	}
}
