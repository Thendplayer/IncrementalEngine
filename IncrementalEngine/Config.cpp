#include "Config.h"
#include "StringUtils.h"

namespace IncrementalEngine
{
	Config::Config()
	{
		std::ifstream t(PATH);
		std::string json(
			(std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>()
		);

		std::string error = "";
		auto resources = Json::parse(json, error);

		if (error != "")
		{
			StringAsWCHAR_ptr(error, LPCWSTR Error);
			MessageBox(NULL, Error, L"Config Error", MB_OK);
		}

		auto items = resources.object_items();
		if (items.empty())
		{
			MessageBox(NULL, L"Resources load failed. Check file structure.", L"Config Error", MB_OK);
		}

		HRESULT result;
		for (auto const& item : items)
		{
			auto obj = item.second.object_items().begin();
			ReadConfigElement(item.first, obj->first, obj->second);
		}
	}
	
	//TODO: Refactor from here down

	void Config::ReadConfigElement(std::string name, std::string type, Json object)
	{
		if (type == "string")
		{
			ReadString(name, object.string_value());
		}

		if (type == "int")
		{
			ReadInt(name, object.int_value());
		}

		if (type == "float")
		{
			ReadFloat(name, object.number_value());
		}

		if (type == "bool")
		{
			ReadBool(name, object.bool_value());
		}

		if (type == "vector2")
		{
			auto items = object.object_items();
			D3DXVECTOR2 vector = D3DXVECTOR2(
				(items.find("x")->second).number_value(),
				(items.find("y")->second).number_value()
			);
			ReadVector2(name, vector);
		}

		if (type == "color")
		{
			auto items = object.object_items();
			D3DXVECTOR4 vector = D3DXVECTOR4(
				(items.find("r")->second).number_value(),
				(items.find("g")->second).number_value(),
				(items.find("b")->second).number_value(),
				(items.find("a")->second).number_value()
			);
			ReadColor(name, vector);
		}
	}
	
	void Config::ReadString(std::string name, std::string object)
	{
		if (name == "ApplicationName") 
		{
			ApplicationName = object;
		}
	}
	
	void Config::ReadInt(std::string name, int object)
	{
	}
	
	void Config::ReadFloat(std::string name, float object)
	{
		if (name == "ScreenDepth")
			ScreenDepth = object;

		if (name == "ScreenNear")
			ScreenNear = object;
	}
	
	void Config::ReadBool(std::string name, bool object)
	{
		if (name == "Fullscreen")
			Fullscreen = object;

		if (name == "VsyncEnabled")
			VsyncEnabled = object;

		if (name == "ShowCursor")
			ShowCursor = object;
	}
	
	void Config::ReadVector2(std::string name, D3DXVECTOR2 object)
	{
		if (name == "WindowSize")
			WindowSize = object;
	}
	
	void Config::ReadColor(std::string name, D3DXVECTOR4 object)
	{
		if (name == "BackgroundColor")
			BackgroundColor = object;
	}
}
