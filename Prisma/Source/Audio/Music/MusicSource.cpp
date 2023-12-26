#include "MusicSource.h"

#include <AL/al.h>

namespace Prisma::Audio {
	MusicSource::MusicSource(MusicSourceID id) : m_ID(id) {
	}

	void MusicSource::Load(const Music &music) {
		m_MusicID = music.GetID();

		alGenSources(1, &m_ALID);
		alSourcef(m_ALID, AL_PITCH, 1.f);
		alSourcef(m_ALID, AL_GAIN, 1.f);
		alSource3f(m_ALID, AL_POSITION, 0.f, 0.f, 0.f);
		alSource3f(m_ALID, AL_VELOCITY, 0.f, 0.f, 0.f);
		alSourcei(m_ALID, AL_LOOPING, true);
		alSourcei(m_ALID, AL_BUFFER, music.GetBufferALID());
	}

	void MusicSource::Clean() {
		alDeleteSources(1, &m_ALID);
	}

	void MusicSource::Play() const {
		alSourcePlay(m_ALID);
	}

	void MusicSource::Stop() const {
		alSourceStop(m_ALID);
	}
}