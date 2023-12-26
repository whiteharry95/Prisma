#include "SoundEffect.h"

namespace Prisma::Audio {
	Sound::Sound(SoundID id) : m_ID(id) {
	}

	void Sound::Clean() {
		alDeleteBuffers(1, &m_BufferALID);
	}
}