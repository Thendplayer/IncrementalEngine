#ifndef _SOUND_H
#define _SOUND_H

#include <d3d11.h>
#include <string>

#include "al.h"

namespace IncrementalEngine 
{
	#define IS_WAV(fn) fn.substr(fn.find_last_of(".") + 1) == "wav";

	class Sound
	{
	public:
		ALuint Buffer;

		Sound(std::string filename);
		virtual ~Sound();

		HRESULT Init();

	private:
		std::string _filename;
	};
}

#endif