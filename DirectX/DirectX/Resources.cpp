#include "Resources.h"

namespace MyEngine 
{
	Resources::Resources() :
		Error(L""),
		_loadedResources(0),
		_textures()
	{
	}

	Resources::~Resources()
	{
		DELETE_RESOURCES(_textures);
	}

	HRESULT Resources::Load()
	{
		ifstream t(PATH);
		string json(
			(istreambuf_iterator<char>(t)),
			istreambuf_iterator<char>()
		);

		string error = "";
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

	Texture* Resources::GetTexture(string name)
	{
		auto item = _textures.find(name);
		assert("The Texture requested is not loaded." && item != _textures.end());
		return item->second;
	}
	
	HRESULT Resources::GetResourceItem(ResourceItem& resourceItem, pair<const string, Json> item)
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
			string error = "Item load failed. Check file structure. [" + (string)e.what() + "]";
			StringAsWCHAR_ptr(error, Error);
			return CO_E_ERRORINAPP;
		}
	}
	
	void Resources::LoadResource(ResourceItem item)
	{
		if (item.Type == "Texture")
		{
			LoadTextures(item);
			return;
		}
	}

	void Resources::LoadTextures(ResourceItem item)
	{
		auto texture = new Texture(item.Fileroute);
		_textures.insert(_textures.begin(), pair<string, Texture*>(item.Name, texture));
	}
}