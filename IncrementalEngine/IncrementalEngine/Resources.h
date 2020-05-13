#ifndef _RESOURCES_H
#define _RESOURCES_H

#include <cassert>
#include "ThirdParty/json11/json11.hpp"

#include "Utils.h"
#include "Texture.h"
#include "Sound.h"

using json11::Json;

namespace IncrementalEngine 
{
	class ResourcesManager 
	{
		#define PATH "Config/Resources.json"
		#define DELETE_RESOURCES(x) for(auto i = x.begin(); i != x.end(); i++){CHECKED_DELETE(i->second);} x.clear();

	public:
		LPCWSTR Error = L"";

		ResourcesManager();
		virtual ~ResourcesManager();

		HRESULT Load();
		Texture* GetTexture(std::string name);
		Sound* GetSound(std::string name);

	private:
		struct ResourceItem
		{
			std::string Name;
			std::string Type;
			std::string Fileroute;
		};

		Json _loadedResources = nullptr;
		std::map<std::string, Texture*> _textures;
		std::map<std::string, Sound*> _sounds;

		void LoadResource(ResourceItem item);
		HRESULT GetResourceItem(ResourceItem& resourceItem, std::pair<const std::string, Json> item);
	};
}

#endif