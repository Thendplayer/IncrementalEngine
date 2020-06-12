#ifndef _SCENE_H
#define _SCENE_H

#include <vector>
#include "Actor.h"

namespace IncrementalEngine 
{
	class SceneManager : public Drawable
	{
	#define IS_ROOT(actor) actor->GetParent() == nullptr

	public:
		SceneManager(
			RenderWindow* renderWindow,
			ShaderManager* shaderManager,
			ID3D11Device* device
		);
		virtual ~SceneManager();
		
		void Destroy(Actor* actor);

		void Update(float dt);
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
		typename std::enable_if<std::is_base_of<Actor, T>::value, T*>::type Create(Actor* parent = nullptr)
		{
			T* actor = new T();
			CopyParameters(actor);

			actor->SetActive(true);
			actor->Init();
			actor->SetParent(parent);

			auto newItem = SceneItem();
			newItem.Actor = actor;

			_items.push_back(newItem);
			return actor;
		}
	};
}

#endif
