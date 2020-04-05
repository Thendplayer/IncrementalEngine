#ifndef _SCENE_H
#define _SCENE_H

#include <vector>
#include "Drawable.h"

using namespace std;

namespace MyEngine 
{
	class Scene : public Drawable
	{
	public:
		Scene(
			RenderWindow* renderWindow,
			ShaderManager* shaderManager,
			ID3D11Device* device
		);
		~Scene();
		
		void Destroy(Drawable* drawable);

		void Update(float dt);
		virtual HRESULT Draw(ID3D11DeviceContext* deviceContext) override;

	private:
		struct SceneItem 
		{
			bool Destroy;
			Drawable* Drawable;
		};

		vector<SceneItem> _items;
		bool destroyInUpdate;

	public:
		template<typename T>
		T* Create()
		{
			static_assert(std::is_base_of<Drawable, T>::value, L"T must inherit from Drawable");

			T* drawable = new T();
			CopyParameters(drawable);

			auto newItem = SceneItem();
			newItem.Drawable = drawable;

			_items.push_back(newItem);
			return drawable;
		}
	};
}

#endif
