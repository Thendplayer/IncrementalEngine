#include "alc.h"
#include "alut.h"

#include <cassert>

#include "SoundEngine.h"

namespace IncrementalEngine 
{
	SoundEngine::SoundEngine() : 
		_soundOn(true), 
		_pause(false)
	{
		_soundOn = InitAL();
		assert("SoundEngine failed during its inizialization. Sound turned off." && _soundOn);
	}

	SoundEngine::~SoundEngine()
	{
		FinalizeAL();
	}

	void SoundEngine::SetGain(float gain)
	{
		alListenerf(AL_GAIN, gain);
	}

	float SoundEngine::GetGain()
	{
		float gain;
		alGetListenerf(AL_GAIN, &gain);
		return gain;
	}

	bool SoundEngine::Play(const Sound* sound)
	{
		if (_soundOn)
		{
			ALfloat vector[3] = { 0.0f, 0.0f, 0.0f };
			int index = GetSource(false);

			if (index == -1)
			{
				return false;
			}

			alSourcei(_sources[index].Source, AL_BUFFER, sound->Buffer);
			alSourcei(_sources[index].Source, AL_SOURCE_RELATIVE, AL_TRUE);
			alSourcef(_sources[index].Source, AL_PITCH, 1.0f);
			alSourcef(_sources[index].Source, AL_GAIN, 1.0f);
			alSourcefv(_sources[index].Source, AL_POSITION, vector);
			alSourcefv(_sources[index].Source, AL_VELOCITY, vector);
			alSourcefv(_sources[index].Source, AL_DIRECTION, vector);
			alSourcei(_sources[index].Source, AL_LOOPING, AL_FALSE);

			alSourcePlay(_sources[index].Source);
		}

		return true;
	}

	void SoundEngine::Reset()
	{
		Stop();
		Clear();
	}

	void SoundEngine::Pause()
	{
		ALint state;
		std::vector<TInfoSource>::iterator it;
		_pause = !_pause;

		for (it = _sources.begin(); it != _sources.end(); ++it)
		{
			alGetSourcei((*it).Source, AL_SOURCE_STATE, &state);
			if (state == AL_PLAYING && _pause)
			{
				alSourcePause((*it).Source);
			}
			else if (state == AL_PAUSED && !_pause)
			{
				alSourcePlay((*it).Source);
			}
		}
	}

	void SoundEngine::Stop()
	{
		ALint state;
		std::vector<TInfoSource>::iterator it;

		for (it = _sources.begin(); it != _sources.end(); ++it)
		{
			alGetSourcei((*it).Source, AL_SOURCE_STATE, &state);
			if (state == AL_PLAYING || state == AL_PAUSED)
			{
				alSourceStop((*it).Source);
			}
		}
	}

	int SoundEngine::CreateSource()
	{
		return GetSource(true);
	}

	bool SoundEngine::DeleteSource(unsigned int source)
	{
		if (source >= 0 && source < _sources.size())
		{
			StopSource(source);
			_sources[source].Reserved = false;
		}
		
		return true;
	}

	bool SoundEngine::PlaySource(unsigned int source, const Sound* sound, bool loop)
	{
		if (_soundOn)
		{
			if (source >= 0 && source < _sources.size() && _sources[source].Reserved)
			{
				StopSource(source);

				alSourcei(_sources[source].Source, AL_BUFFER, sound->Buffer);
				alSourcef(_sources[source].Source, AL_PITCH, 1.0f);
				alSourcef(_sources[source].Source, AL_GAIN, 1.0f);
				alSourcei(_sources[source].Source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);

				alSourcePlay(_sources[source].Source);

				return true;
			}
			else
			{
				return false;
			}
		}

		return true;
	}

	bool SoundEngine::PauseSource(unsigned int source)
	{
		if (source >= 0 && source < _sources.size() && _sources[source].Reserved)
		{
			ALint state;

			alGetSourcei(_sources[source].Source, AL_SOURCE_STATE, &state);
			if (state == AL_PLAYING)
			{
				alSourcePause(_sources[source].Source);
			}
			else if (state == AL_PAUSED)
			{
				alSourcePlay(_sources[source].Source);
			}
			return true;
		}
		else
		{
			return false;
		}
	}

	bool SoundEngine::StopSource(unsigned int source)
	{
		if (source >= 0 && source < _sources.size() && _sources[source].Reserved)
		{
			ALint state;

			alGetSourcei(_sources[source].Source, AL_SOURCE_STATE, &state);
			if (state == AL_PLAYING || state == AL_PAUSED)
			{
				alSourceStop(_sources[source].Source);
			}

			return true;
		}
		else
		{
			return false;
		}
	}

	bool SoundEngine::SetSourceGain(unsigned int source, float gain)
	{
		if (source >= 0 && source < _sources.size() && _sources[source].Reserved)
		{
			alSourcef(_sources[source].Source, AL_GAIN, gain);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool SoundEngine::GetSourceGain(unsigned int source, float& gain)
	{
		if (source >= 0 && source < _sources.size() && _sources[source].Reserved)
		{
			alGetSourcef(_sources[source].Source, AL_GAIN, &gain);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool SoundEngine::InitAL()
	{
		ALenum error;
		ALCdevice* device = alcOpenDevice(NULL);
		ALCcontext* context = alcCreateContext(device, NULL);

		alcMakeContextCurrent(context);

		if ((error = alcGetError(device)) != ALC_NO_ERROR)
		{
			return false;
		}

		return alutInitWithoutContext(NULL, NULL) == AL_TRUE;
	}

	void SoundEngine::FinalizeAL()
	{
		Clear();

		ALCcontext* context = alcGetCurrentContext();
		ALCdevice* device = alcGetContextsDevice(context);

		alcMakeContextCurrent(NULL);
		alcDestroyContext(context);
		alcCloseDevice(device);
	}

	void SoundEngine::Clear()
	{
		std::vector<TInfoSource>::iterator itSource;
		for (itSource = _sources.begin(); itSource != _sources.end(); ++itSource)
		{
			ALuint source = (*itSource).Source;
			alDeleteSources(1, &source);
		}

		_sources.clear();
	}

	unsigned int SoundEngine::GetSource(bool reserved)
	{
		unsigned int result = 0;
		ALint state;
		ALenum error;

		for (unsigned int i = 0; i < _sources.size(); ++i)
		{
			if (!_sources[i].Reserved)
			{
				alGetSourcei(_sources[i].Source, AL_SOURCE_STATE, &state);
				if (state != AL_PLAYING && state != AL_PAUSED)
				{
					_sources[i].Reserved = reserved;
					return i;
				}
			}
		}

		TInfoSource l_Info;
		alGenSources(1, &l_Info.Source);
		if ((error = alGetError()) != AL_NO_ERROR)
		{
			result = -1;
		}
		else
		{
			l_Info.Reserved = reserved;
			_sources.push_back(l_Info);
			result = (unsigned int)_sources.size() - 1;
		}

		return result;
	}

	std::string SoundEngine::GetALErrorString(ALenum error)
	{
		switch (error)
		{
			case AL_NO_ERROR:
				return std::string("AL_NO_ERROR");
				break;
			case AL_INVALID_NAME:
				return std::string("AL_INVALID_NAME");
				break;
			case AL_INVALID_ENUM:
				return std::string("AL_INVALID_ENUM");
				break;
			case AL_INVALID_VALUE:
				return std::string("AL_INVALID_VALUE");
				break;
			case AL_INVALID_OPERATION:
				return std::string("AL_INVALID_OPERATION");
				break;
			case AL_OUT_OF_MEMORY:
				return std::string("AL_OUT_OF_MEMORY");
				break;
		}

		return "";
	}
}