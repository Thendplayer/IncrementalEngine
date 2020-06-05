#include <algorithm>

#include "Scene.h"
#include "Utils.h"

namespace IncrementalEngine 
{
	SceneManager::SceneManager(
		RenderWindow* renderWindow, 
		ShaderManager* shaderManager, 
		ID3D11Device* device
	)
	{
		_renderWindow = renderWindow; 
		_shaderManager = shaderManager; 
		_device = device;
	}

	SceneManager::~SceneManager()
	{
		bool clear = false;
		while (!clear) 
		{
			clear = true;
			for (int i = 0; i < _items.size(); i++)
			{
				if (_items[i].Destroy) continue;

				if (IS_ROOT(_items[i].Actor))
				{
					CHECKED_DELETE(_items[i].Actor);
					_items[i].Destroy = true;
					clear = false;
				}
			}
		}

		_items.clear();
	}

	void SceneManager::Destroy(Actor* actor)
	{
		for (int i = 0; i < _items.size(); i++)
		{
			if (_items[i].Actor == actor)
			{
				_items[i].Destroy = true;
				break;
			}
		}

		_destroyInUpdate = true;
	}

	void SceneManager::Update(float dt)
	{
		if (_destroyInUpdate)
		{
			for (int i = 0; i < _items.size(); i++)
			{
				if (_items[i].Destroy)
				{
					CHECKED_DELETE(_items[i].Actor);
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

			_destroyInUpdate = false;
		}

		for (int i = 0; i < _items.size(); i++)
		{
			if (IS_ROOT(_items[i].Actor))
			{
				_items[i].Actor->UpdateRecursive(dt);
			}
		}
	}

	HRESULT SceneManager::Draw(ID3D11DeviceContext* deviceContext)
	{
		HRESULT result;

		for (int i = 0; i < _items.size(); i++)
		{
			if (IS_ROOT(_items[i].Actor))
			{
				result = _items[i].Actor->DrawRecursive(deviceContext);

				if (FAILED(result))
				{
					return CO_E_ERRORINAPP;
				}
			}
		}

		return S_OK;
	}
}