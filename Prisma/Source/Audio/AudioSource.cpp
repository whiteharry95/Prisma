#include "AudioSource.h"

#include <AL/al.h>

namespace Prisma::Audio {
	AudioSource::AudioSource(AudioSourceID id) : m_ID(id) {
	}

	void AudioSource::Load(const SoundEffect &soundEffect) {
		m_SoundEffectID = soundEffect.GetID();

		alGenSources(1, &m_ALID);
		alSourcef(m_ALID, AL_PITCH, 1.f);
		alSourcef(m_ALID, AL_GAIN, 1.f);
		alSource3f(m_ALID, AL_POSITION, 0.f, 0.f, 0.f);
		alSource3f(m_ALID, AL_VELOCITY, 0.f, 0.f, 0.f);
		alSourcei(m_ALID, AL_LOOPING, AL_FALSE);
		alSourcei(m_ALID, AL_BUFFER, soundEffect.GetBufferALID());
	}

	void AudioSource::Clean() {
		alDeleteSources(1, &m_ALID);
	}

	void AudioSource::Play() const {
		alSourcePlay(m_ALID);
	}

	void AudioSource::Stop() const {
		alSourceStop(m_ALID);
	}
}