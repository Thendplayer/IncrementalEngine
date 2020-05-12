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

		void Center();

		virtual FloatRect GetLocalBounds();
		FloatRect GetGlobalBounds();

		const Transform GetCombinedTransform();
		const D3DXVECTOR2 GetCombinedTranslation();
		const D3DXVECTOR2 GetCombinedScale();
		const float GetCombinedRotation();

		Actor* GetParent() const;
		void SetParent(Actor* value);

		virtual void Init();
		virtual void Update();

		void SetActive(bool active);
		bool IsActive();

		void UpdateRecursive();
		HRESULT DrawRecursive(ID3D11DeviceContext* deviceContext);

		virtual HRESULT Draw(ID3D11DeviceContext* deviceContext) override;

	private:
		Actor* _parent;
		vector<Actor*> _children;
		bool _active;

		const Transform GetWorldTransform() const;
		
		D3DXVECTOR2 GetWorldPosition() const;
		void SetWorldPosition(D3DXVECTOR2 value);
	};
}

#endif