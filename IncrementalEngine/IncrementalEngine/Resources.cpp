#include "Resources.h"

namespace IncrementalEngine 
{
	Resources::Resources() :
		Error(L""),
		_loadedResources(0),
		_sounds(),
		_textures()
	{
	}

	Resources::~Resources()
	{
		DELETE_RESOURCES(_textures);
		DELETE_RESOURCES(_sounds);
	}

	HRESULT Resources::Load()
	{
		std::ifstream t(PATH);
		std::string json(
			(std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>()
		);

		std::string error = "";
		_loadedResources = Json::parse(json, error);

		if (error != "")
		{
			StringAsWCHAR_ptr(error, Error)
			return CO_E_ERRORINAPP;
		}

		auto items = _loadedResources.object_items();
		if (items.empty())
		{
			Error = L"Resources load failed. Check file structure.";
			return CO_E_ERRORINAPP;
		}

		HRESULT result;
		for (auto const& item : items)
		{
			ResourceItem resourceItem;
			result = GetResourceItem(resourceItem, item);

			if (FAILED(result))
			{
				return CO_E_ERRORINAPP;
			}

			LoadResource(resourceItem);
		}

		return S_OK;
	}

	Texture* Resources::GetTexture(std::string name)
	{
		auto item = _textures.find(name);
		assert("The Texture requested is not loaded." && item != _textures.end());
		return item->second;
	}

	Sound* Resources::GetSound(std::string name)
	{
		auto item = _sounds.find(name);
		assert("The Sound requested is not loaded." && item != _sounds.end());
		return item->second;
	}
	
	HRESULT Resources::GetResourceItem(ResourceItem& resourceItem, std::pair<const std::string, Json> item)
	{
		try
		{
			resourceItem = ResourceItem{
				item.first, //Name
				item.second["Type"].string_value(), //Type
				item.second["Fileroute"].string_value() //Fileroute
			};

			return S_OK;
		}
		catch (const std::exception& e)
		{
			std::string error = "Item load failed. Check file structure. [" + (std::string)e.what() + "]";
			StringAsWCHAR_ptr(error, Error);
			return CO_E_ERRORINAPP;
		}
	}
	
	void Resources::LoadResource(ResourceItem item)
	{
		if (item.Type == "Texture")
		{
			Texture* texture = new Texture(item.Fileroute);
			_textures.insert(_textures.begin(), std::pair<std::string, Texture*>(item.Name, texture));
			
			return;
		}
		
		if (item.Type == "Sound")
		{
			Sound* sound = new Sound(item.Fileroute);
			sound->Init();
			_sounds.insert(_sounds.begin(), std::pair<std::string, Sound*>(item.Name, sound));
		
			return;
		}
	}
}