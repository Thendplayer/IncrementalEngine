#include "TextureBase.h"

namespace MyEngine 
{
	TextureBase::TextureBase() :
		_texture(NULL),
		_position(0, 0),
		_scale(1, 1)
	{
	}

	void TextureBase::Update(D3DXVECTOR2 position, D3DXVECTOR2 scale)
	{
		_position = position;
		_scale = scale;
	}

	Texture* TextureBase::GetTexture()
	{
		return _texture;
	}
	
	D3DXVECTOR2 TextureBase::GetScaledSize()
	{
		auto textureSize = _texture->GetSize();
		return D3DXVECTOR2(textureSize.x * _scale.x, textureSize.y * _scale.y);
	}
}
