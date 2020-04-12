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
	}

	HRESULT Resources::Load(ID3D11Device* device)
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
			Error = StringUtils::AsWCHAR_ptr(error);
			return FALSE;
		}

		auto items = _loadedResources.object_items();
		if (items.empty())
		{
			Error = L"Resources load failed. Check file structure.";
			return FALSE;
		}

		HRESULT result;
		for (auto const& item : items)
		{
			ResourceItem resourceItem;
			result = GetResourceItem(resourceItem, item);

			if (FAILED(result))
			{
				return FALSE;
			}

			LoadResource(device, resourceItem);
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
				StringUtils::AsWCHAR_ptr(item.second["Fileroute"].string_value()) //Filename
			};

			return S_OK;
		}
		catch (const std::exception& e)
		{
			string error = "Item load failed. Check file structure. [" + (string)e.what() + "]";
			Error = StringUtils::AsWCHAR_ptr(error);
			return FALSE;
		}
	}
	
	void Resources::LoadResource(ID3D11Device* device, ResourceItem item)
	{
		if (item.Type == "Texture")
		{
			LoadTextures(device, item);
			return;
		}
	}

	void Resources::LoadTextures(ID3D11Device* device, ResourceItem item)
	{
		auto texture = new Texture();
		texture->Init(device, item.Fileroute);
		_textures.insert(_textures.begin(), pair<string, Texture*>(item.Name, texture));
	}
}