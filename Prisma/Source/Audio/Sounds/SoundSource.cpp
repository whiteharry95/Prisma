#include "SoundSource.h"

#include <AL/al.h>

namespace Prisma::Audio {
	SoundSource::SoundSource(SoundSourceID id) : m_ID(id) {
	}

	void SoundSource::Load(const Sound &sound) {
		m_SoundID = sound.GetID();

		alGenSources(1, &m_ALID);
		alSourcef(m_ALID, AL_PITCH, 1.f);
		alSourcef(m_ALID, AL_GAIN, 1.f);
		alSource3f(m_ALID, AL_POSITION, 0.f, 0.f, 0.f);
		alSource3f(m_ALID, AL_VELOCITY, 0.f, 0.f, 0.f);
		alSourcei(m_ALID, AL_LOOPING, AL_FALSE);
		alSourcei(m_ALID, AL_BUFFER, sound.GetBufferALID());
	}

	void SoundSource::Clean() {
		alDeleteSources(1, &m_ALID);
	}

	void SoundSource::Play() const {
		alSourcePlay(m_ALID);
	}

	void SoundSource::Stop() const {
		alSourceStop(m_ALID);
	}
}