#ifndef _ACTOR_H
#define _ACTOR_H

#include<vector>
#include<algorithm>

#include "Drawable.h"
#include "Transformable.h"

namespace IncrementalEngine
{
	class Actor : public Transformable, public Drawable
	{
	public:
		virtual ~Actor();

		virtual void Init();
		virtual void Update(float dt);
		virtual HRESULT Draw(ID3D11DeviceContext* deviceContext) override;

		void UpdateRecursive(float dt);
		HRESULT DrawRecursive(ID3D11DeviceContext* deviceContext);

		virtual FloatRect GetLocalBounds();
		FloatRect GetGlobalBounds();

		void Center();

		const Transform GetWorldTransform();
		const D3DXVECTOR2 GetWorldPosition();
		const D3DXVECTOR2 GetWorldScale();
		const float GetWorldRotation();
		
		void SetWorldPosition(D3DXVECTOR2 value);

		virtual void SetPosition(float x, float y) override;
		virtual void SetPosition(const D3DXVECTOR2& position) override;
		virtual const D3DXVECTOR2& GetPosition() const override;

		Actor* GetParent() const;
		virtual void SetParent(Actor* value, const bool fixWorldPosition = true);

		void SetActive(bool active);
		bool IsActive();

	private:
		Actor* _parent;
		vector<Actor*> _children;
		bool _active;
	};
}

#endif