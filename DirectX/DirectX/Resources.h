#ifndef _RESOURCES_H
#define _RESOURCES_H

#include <cassert>
#include "ThirdParty/json11/json11.hpp"

#include "Utils.h"
#include "Texture.h"
#include "Sound.h"

using json11::Json;
using namespace std;

namespace IncrementalEngine 
{
	class Resources 
	{
		#define PATH "Config/Resources.json"
		#define DELETE_RESOURCES(x) for(auto i = x.begin(); i != x.end(); i++){CHECKED_DELETE(i->second);} x.clear();

	public:
		LPCWSTR Error = L"";

		Resources();
		virtual ~Resources();

		HRESULT Load();
		Texture* GetTexture(string name);
		Sound* GetSound(string name);

	private:
		struct ResourceItem
		{
			string Name;
			string Type;
			string Fileroute;
		};

		Json _loadedResources = nullptr;
		map<string, Texture*> _textures;
		map<string, Sound*> _sounds;

		void LoadResource(ResourceItem item);
		HRESULT GetResourceItem(ResourceItem& resourceItem, pair<const string, Json> item);
	};
}

#endif