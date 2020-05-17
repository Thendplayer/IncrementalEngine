#ifndef _SAVE_SYSTEM_H
#define _SAVE_SYSTEM_H

#include <fstream>
#include <sstream>
#include <string>

namespace IncrementalEngine 
{
	#define SAVE_EXTENSION ".ie"
	#define SAVES_PATH (std::filesystem::current_path().string() + "\\Saves\\")

	class SaveSystem
	{
	public:
		SaveSystem();

		void SaveInt(int value, std::string key);
		void SaveFloat(float value, std::string key);
		void SaveString(std::string value, std::string key);
		
		int GetInt(std::string key);
		float GetFloat(std::string key);
		std::string GetString(std::string key);

		bool HasKey(std::string key);
		bool DeleteKey(std::string key);
		void DeleteAll();
	};
}

#endif