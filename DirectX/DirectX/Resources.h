#ifndef _RESOURCES_H
#define _RESOURCES_H

#include <cassert>
#include "ThirdParty/json11/json11.hpp"

#include "StringUtils.h"
#include "Texture.h"

using json11::Json;
using namespace std;

namespace MyEngine 
{
	class Resources 
	{
		#define PATH "../DirectX/Config/Resources.json"

	public:
		LPCWSTR Error = L"";

		Resources();
		~Resources();

		HRESULT Load(ID3D11Device* device);
		Texture* GetTexture(string name);

	private:
		struct ResourceItem
		{
			string Name;
			string Type;
			WCHAR* Fileroute;
		};

		Json _loadedResources = nullptr;
		map<string, Texture*> _textures;

		void LoadResource(ID3D11Device* device, ResourceItem item);
		void LoadTextures(ID3D11Device* device, ResourceItem item);
		HRESULT GetResourceItem(ResourceItem& resourceItem, pair<const string, Json> item);
	};
}

#endif