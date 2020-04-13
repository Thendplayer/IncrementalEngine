#ifndef _RESOURCES_H
#define _RESOURCES_H

#include <cassert>
#include "ThirdParty/json11/json11.hpp"

#include "Utils.h"
#include "Texture.h"

using json11::Json;
using namespace std;

namespace MyEngine 
{
	class Resources 
	{
		#define PATH "../DirectX/Config/Resources.json"
		#define DELETE_RESOURCES(x) for(auto i = x.begin(); i != x.end(); i++){CHECKED_DELETE(i->second);} x.clear();

	public:
		LPCWSTR Error = L"";

		Resources();
		~Resources();

		HRESULT Load();
		Texture* GetTexture(string name);

	private:
		struct ResourceItem
		{
			string Name;
			string Type;
			string Fileroute;
		};

		Json _loadedResources = nullptr;
		map<string, Texture*> _textures;

		void LoadResource(ResourceItem item);
		void LoadTextures(ResourceItem item);
		HRESULT GetResourceItem(ResourceItem& resourceItem, pair<const string, Json> item);
	};
}

#endif