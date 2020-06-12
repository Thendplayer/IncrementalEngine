#include "SaveSystem.h"
#include <filesystem>
#include <Shlobj.h>

namespace IncrementalEngine 
{
	SaveSystem::SaveSystem()
	{
		struct stat info;
		if (stat(SAVES_PATH.c_str(), &info) != 0)
		{
			if (!std::filesystem::create_directory(SAVES_PATH.c_str()))
			{
				MessageBox(NULL, L"Failed to create Saves Path", L"SaveSystem Error", MB_OK);
			}
		}
	}

	void SaveSystem::SaveInt(int value, std::string key)
	{
		std::ofstream out(SAVES_PATH + key + SAVE_EXTENSION, std::ofstream::trunc);
		out << value;
		out.close();
	}

	void SaveSystem::SaveFloat(float value, std::string key)
	{
		std::ofstream out(SAVES_PATH + key + SAVE_EXTENSION, std::ofstream::trunc);
		out << value;
		out.close();
	}

	void SaveSystem::SaveString(std::string value, std::string key)
	{
		std::ofstream out(SAVES_PATH + key + SAVE_EXTENSION, std::ofstream::trunc);
		out << value;
		out.close();
	}

	int SaveSystem::GetInt(std::string key)
	{
		std::string content = GetString(key);

		try
		{
			return std::stoi(content);
		}
		catch (std::invalid_argument const& e)
		{
			MessageBox(NULL, L"Bad input : std::invalid_argument thrown", L"SaveSystem", MB_OK);
		}
		catch (std::out_of_range const& e)
		{
			MessageBox(NULL, L"Integer overflow: std::out_of_range thrown", L"SaveSystem", MB_OK);
		}

		return NULL;
	}

	float SaveSystem::GetFloat(std::string key)
	{
		std::string content = GetString(key);

		try
		{
			return std::stof(content);
		}
		catch (std::invalid_argument const& e)
		{
			MessageBox(NULL, L"Bad input : std::invalid_argument thrown", L"SaveSystem", MB_OK);
		}
		catch (std::out_of_range const& e)
		{
			MessageBox(NULL, L"Integer overflow: std::out_of_range thrown", L"SaveSystem", MB_OK);
		}

		return NULL;
	}

	std::string SaveSystem::GetString(std::string key)
	{
		std::ifstream file(SAVES_PATH + key + SAVE_EXTENSION);
		if (!file.good()) return "0";

		std::string content(
			(std::istreambuf_iterator<char>(file)),
			(std::istreambuf_iterator<char>())
		);

		return content;
	}

	bool SaveSystem::HasKey(std::string key)
	{
		std::ifstream file((SAVES_PATH + key + SAVE_EXTENSION).c_str());
		return file.good();
	}

	bool SaveSystem::DeleteKey(std::string key)
	{
		return remove((SAVES_PATH + key + SAVE_EXTENSION).c_str()) == 0;
	}
	
	void SaveSystem::DeleteAll()
	{
		std::filesystem::remove_all("myDirectory");
	}
}