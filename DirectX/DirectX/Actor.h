#ifndef _ACTOR_H
#define _ACTOR_H

#include<vector>
#include<algorithm>

#include "Bitmap.h"
#include "Transformable.h"

namespace MyEngine
{
	class Actor : public Transformable, public Drawable
	{
	public:
		Actor();
		~Actor();

		void SetTexture(Texture* texture);
		void ClearTexture();

		void Center();

		FloatRect GetLocalBounds();
		FloatRect GetGlobalBounds();

		Actor* GetParent() const;
		void SetParent(Actor* value);

		virtual void Init();
		virtual void Update();

		void UpdateRecursive();
		HRESULT DrawRecursive(ID3D11DeviceContext* deviceContext);

		virtual HRESULT Draw(ID3D11DeviceContext* deviceContext) override;

	private:
		Actor* _parent;
		vector<Actor*> _children;
		TextureBase* _texture;

		const Transform* GetWorldTransform() const;
		
		D3DXVECTOR2 GetWorldPosition() const;
		void SetWorldPosition(D3DXVECTOR2 value);
	};
}

#endif