#include "SoundSource.h"

#include <AL/al.h>

#include "../../Debugging.h"

namespace Prisma::Audio {
	SoundSource::SoundSource(SoundSourceID id, bool deactivateOnStop, bool loop) : m_ID(id), m_DeactivateOnStop(deactivateOnStop) {
		alGenSources(1, &m_ALID);
		alSourcei(m_ALID, AL_LOOPING, loop);
	}

	void SoundSource::Update() {
		if (!m_Active) {
			return;
		}

		int state;
		alGetSourcei(m_ALID, AL_SOURCE_STATE, &state);

		if (m_DeactivateOnStop && state == AL_STOPPED) {
			Deactivate();
		}
	}

	void SoundSource::Clean() {
		alDeleteSources(1, &m_ALID);
	}

	void SoundSource::Play(const Sound &sound, float gain, float pitch) {
		if (!m_Active) {
			Debugging::LogWarning("Attempting to play an inactive sound source");
			return;
		}

		alSourceRewind(m_ALID);

		alSourcei(m_ALID, AL_BUFFER, sound.GetBufferALID());
		alSourcef(m_ALID, AL_GAIN, gain);
		alSourcef(m_ALID, AL_PITCH, pitch);

		alSourcePlay(m_ALID);
	}

	void SoundSource::Deactivate() {
		alSourceStop(m_ALID);
		m_Active = false;
	}
}