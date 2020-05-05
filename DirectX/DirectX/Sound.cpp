//#include "alut.h"
//
//#include "Sound.h"
//
//namespace MyEngine 
//{
//	Sound::Sound(std::string filename) :
//		_filename(filename),
//		Buffer(NULL)
//	{
//	}
//
//	Sound::~Sound()
//	{
//		alDeleteBuffers(1, &Buffer);
//	}
//
//	HRESULT Sound::Init()
//	{
//		FILE* file;
//		ALenum error;
//		ALuint buffer;
//
//		alGenBuffers(1, &buffer);
//
//		if ((error = alGetError()) != AL_NO_ERROR)
//		{
//			alDeleteBuffers(1, &buffer);
//			return CO_E_ERRORINAPP;
//		}
//
//		fopen_s(&file, _filename.c_str(), "r");
//		if (file == NULL)
//		{
//			alDeleteBuffers(1, &buffer);
//			return CO_E_ERRORINAPP;
//		}
//		else
//		{
//			fclose(file);
//		}
//
//		buffer = alutCreateBufferFromFile(_filename.c_str());
//
//		if ((error = alGetError()) != AL_NO_ERROR)
//		{
//			alDeleteBuffers(1, &buffer);
//			return CO_E_ERRORINAPP;
//		}
//
//		Buffer = buffer;
//
//		return S_OK;
//	}
//}
