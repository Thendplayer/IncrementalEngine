#ifndef _SOUND_ENGINE_H
#define _SOUND_ENGINE_H

#include <d3dx11.h>
#include <xnamath.h>
#include <D3DX10.h>

#include <string>
#include <map>
#include <vector>

#include "Sound.h"

namespace IncrementalEngine
{
	class SoundEngine
	{
	public:
		SoundEngine();
		virtual ~SoundEngine();

		void Reset();
		void Pause();
		void Stop();
		void SoundOn() { _soundOn = true; }
		void SoundOff() { _soundOn = false; }
		void SetGain(float gain);
		float GetGain();

		bool Play(const Sound* sound);

		int CreateSource();
		bool DeleteSource(unsigned int source);
		bool PlaySource(unsigned int source, const Sound* sound, bool loop);
		bool PauseSource(unsigned int source);
		bool StopSource(unsigned int source);
		bool SetSourceGain(unsigned int source, float inGain);
		bool GetSourceGain(unsigned int source, float& outGain);

	private:
		struct TInfoSource
		{
			ALuint						Source;
			bool						Reserved;
		};

		bool _soundOn;
		bool _pause;

		std::vector<TInfoSource> _sources;

		bool InitAL();
		void FinalizeAL();
		void Clear();
		unsigned int GetSource(bool reserved = false);
		std::string GetALErrorString(ALenum error);
	};
}

#endif
