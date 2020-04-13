#ifndef _TEXTURE_BASE_H
#define _TEXTURE_BASE_H

#include <d3d11.h>
#include <d3dx10math.h>

#include "Texture.h"
#include "Drawable.h"

namespace MyEngine 
{
	class TextureBase : virtual public Drawable
	{
	public:
		TextureBase();

		void Update(D3DXVECTOR2 position, D3DXVECTOR2 scale);

		Texture* GetTexture();
		D3DXVECTOR2 GetScaledSize();

	protected:
		Texture* _texture;

		D3DXVECTOR2 _position;
		D3DXVECTOR2 _scale;
	};
}

#endif