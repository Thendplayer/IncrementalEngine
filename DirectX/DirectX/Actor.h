#ifndef _ACTOR_H
#define _ACTOR_H

#include<vector>
#include"Drawable.h"
#include"Transformable.h"

using namespace std;

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
		
		Vector2f* GetWorldPosition() const;
		void SetWorldPosition(Vector2f* value);

		Actor* GetParent() const;
		void SetParent(Actor* value);
	};
}

#endif