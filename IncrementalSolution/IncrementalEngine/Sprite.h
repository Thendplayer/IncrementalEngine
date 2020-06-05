#ifndef _SPRITE_H
#define _SPRITE_H

#include "Actor.h"
#include "Bitmap.h"

namespace IncrementalEngine 
{
	class Sprite : public Actor
	{
	public:
		Sprite();
		virtual ~Sprite() override;

		void SetTexture(Texture* texture);
		void ClearTexture();

		virtual FloatRect GetLocalBounds() override;

		virtual void Update(float dt) override;
		virtual HRESULT Draw(ID3D11DeviceContext* deviceContext) override;

	private:
		TextureBase* _texture;
	};
}

#endif