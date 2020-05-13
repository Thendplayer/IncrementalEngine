#ifndef _TEXTURE_BASE_H
#define _TEXTURE_BASE_H

#include <d3d11.h>
#include <d3dx10math.h>

#include "Texture.h"
#include "Drawable.h"
#include "Transform.h"
#include "FloatRect.h"

namespace IncrementalEngine 
{
	class TextureBase : virtual public Drawable
	{
	public:
		TextureBase();
		virtual ~TextureBase();

		void Update(Transform transform, FloatRect bounds);

		Texture* GetTexture();
		D3DXVECTOR2 GetSize();

	protected:
		Texture* _texture;
		Transform _transform;
		FloatRect _bounds;
	};
}

#endif