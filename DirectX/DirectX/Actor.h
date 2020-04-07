#ifndef _ACTOR_H
#define _ACTOR_H

#include<vector>
#include<algorithm>
#include"Drawable.h"
#include"Transformable.h"

namespace MyEngine
{
	class Actor : public Transformable, public Drawable
	{
	public:
		Actor();
		~Actor();

		void Center();

		RECT* GetLocalBounds();
		RECT* GetGlobalBounds();

		void Update(float dt);
		void UpdateRecursive(float dt);

		void DrawRecursive(ID3D11DeviceContext* deviceContext);

		virtual HRESULT Draw(ID3D11DeviceContext* deviceContext) override;

	private:
		Actor* _parent;
		vector<Actor*> _children;

		Transform* GetWorldTransform() const;
		
		D3DXVECTOR2* GetWorldPosition() const;
		void SetWorldPosition(D3DXVECTOR2* value);

		Actor* GetParent() const;
		void SetParent(Actor* value);
	};
}

#endif