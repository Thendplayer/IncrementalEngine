#ifndef _CONFIG_H
#define _CONFIG_H

#include <string>
#include <D3DX10.h>

#include "ThirdParty/json11/json11.hpp"

using json11::Json;

namespace IncrementalEngine 
{
	struct Config
	{
		#define PATH "Config/Config.json"

	public:
		std::string ApplicationName;

		bool Fullscreen;
		D3DXVECTOR2 WindowSize;

		float ScreenDepth;
		float ScreenNear;
		bool VsyncEnabled;

		bool ShowCursor;

		D3DXVECTOR4 BackgroundColor;

		Config();

	private:
		void ReadConfigElement(std::string name, std::string type, Json object);
		
		void ReadString(std::string name, std::string object);
		void ReadInt(std::string name, int object);
		void ReadFloat(std::string name, float object);
		void ReadBool(std::string name, bool object);
		void ReadVector2(std::string name, D3DXVECTOR2 object);
		void ReadColor(std::string name, D3DXVECTOR4 object);
	};
}

#endif