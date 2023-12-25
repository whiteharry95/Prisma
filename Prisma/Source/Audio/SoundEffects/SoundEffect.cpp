#include "SoundEffect.h"

namespace Prisma::Audio {
	SoundEffect::SoundEffect(SoundEffectID id) : m_ID(id) {
	}

	void SoundEffect::Clean() {
		alDeleteBuffers(1, &m_BufferALID);
	}
}