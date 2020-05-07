#ifndef _SPRITE_H
#define _SPRITE_H

#include "Actor.h"
#include "Bitmap.h"

namespace MyEngine 
{
	class Sprite : public Actor
	{
	public:
		Sprite();
		~Sprite();

		void SetTexture(Texture* texture);
		void ClearTexture();

		virtual FloatRect GetLocalBounds() override;

		virtual void Update() override;
		virtual HRESULT Draw(ID3D11DeviceContext* deviceContext) override;

	private:
		TextureBase* _texture;
	};
}

#endif