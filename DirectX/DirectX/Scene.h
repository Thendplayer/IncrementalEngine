#ifndef _SCENE_H
#define _SCENE_H

#include <vector>
#include "Actor.h"

using namespace std;

namespace MyEngine 
{
	class Scene : public Drawable
	{
	#define IS_ROOT(actor) actor->GetParent() == nullptr

	public:
		Scene(
			RenderWindow* renderWindow,
			ShaderManager* shaderManager,
			ID3D11Device* device
		);
		virtual ~Scene();
		
		void Destroy(Actor* drawable);

		void Update();
		virtual HRESULT Draw(ID3D11DeviceContext* deviceContext) override;

	private:
		struct SceneItem 
		{
			bool Destroy;
			Actor* Actor;
		};

		vector<SceneItem> _items;
		bool _destroyInUpdate;

	public:
		//T must inherit from Actor
		template<typename T>
		typename std::enable_if<std::is_base_of<Actor, T>::value, T*>::type Create()
		{
			T* actor = new T();
			CopyParameters(actor);

			actor->SetActive(true);
			actor->Init();

			auto newItem = SceneItem();
			newItem.Actor = actor;

			_items.push_back(newItem);
			return actor;
		}
	};
}

#endif
