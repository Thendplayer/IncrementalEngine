#include <algorithm>

#include "Scene.h"
#include "Utils.h"

namespace MyEngine 
{
	Scene::Scene(
		RenderWindow* renderWindow, 
		ShaderManager* shaderManager, 
		ID3D11Device* device
	)
	{
		_renderWindow = renderWindow; 
		_shaderManager = shaderManager; 
		_device = device;
	}

	Scene::~Scene()
	{
		if (!_items.empty())
		{
			for (int i = 0; i < _items.size(); i++)
			{
				CHECKED_DELETE(_items[i].Drawable);
			}
			_items.clear();
		}
	}

	void Scene::Destroy(Drawable* drawable)
	{
		for (int i = 0; i < _items.size(); i++)
		{
			if (_items[i].Drawable == drawable)
			{
				_items[i].Destroy = true;
				break;
			}
		}

		destroyInUpdate = true;
	}

	void Scene::Update(float dt)
	{
		if (destroyInUpdate)
		{
			for (int i = 0; i < _items.size(); i++)
			{
				if (_items[i].Destroy)
				{
					CHECKED_DELETE(_items[i].Drawable);
				}
			}
		
			_items.erase(
				remove_if(
					_items.begin(), 
					_items.end(), 
					[](const SceneItem& item) {
						return item.Destroy;
					}
				), 
				_items.end()
			);

			destroyInUpdate = false;
		}
	}

	HRESULT Scene::Draw(ID3D11DeviceContext* deviceContext)
	{
		HRESULT result;

		for (int i = 0; i < _items.size(); i++)
		{
			result = _items[i].Drawable->Draw(deviceContext);
			
			if (FAILED(result))
			{
				return FALSE;
			}
		}

		return S_OK;
	}
}