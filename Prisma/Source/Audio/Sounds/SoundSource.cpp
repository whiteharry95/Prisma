#include "SoundSource.h"

#include <AL/al.h>

#include "../../Debugging.h"

namespace Prisma::Audio {
	SoundSource::SoundSource(SoundSourceID id) : m_ID(id) {
	}

	void SoundSource::Init(const Sound sound) {
		if (m_Initialised) {
			Debugging::LogWarning("Attempting to initialise a sound that has already been initialised");
			return;
		}

		m_SoundID = sound.GetID();

		alGenSources(1, &m_ALID);
		alSourcef(m_ALID, AL_PITCH, 1.f);
		alSourcef(m_ALID, AL_GAIN, 1.f);
		alSource3f(m_ALID, AL_POSITION, 0.f, 0.f, 0.f);
		alSource3f(m_ALID, AL_VELOCITY, 0.f, 0.f, 0.f);
		alSourcei(m_ALID, AL_LOOPING, false);
		alSourcei(m_ALID, AL_BUFFER, sound.GetBufferALID());

		m_Initialised = true;
	}

	void SoundSource::Clean() {
		if (!m_Initialised) {
			Debugging::LogWarning("Attempting to clean an unloaded sound");
			return;
		}

		alDeleteSources(1, &m_ALID);
	}

	void SoundSource::Deactivate() {
		alSourceStop(m_ALID);
	}

	void SoundSource::Play() {
		if (!m_Active) {
			Debugging::LogWarning("Attempting to play an inactive sound source");
			return;
		}

		alSourcePlay(m_ALID);
	}
}