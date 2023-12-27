#pragma once

#include <GLM/glm.hpp>

#include "../ALID.h"
#include "Sound.h"

namespace Prisma::Audio {
	typedef unsigned char SoundSourceID;

	class SoundSource {
		SoundSourceID m_ID;
		ALID m_ALID;

		bool m_Active = true;

		bool m_DeactivateOnStop;

	public:
		SoundSource(SoundSourceID id, bool deactivateOnStop = true, bool loop = false);

		void Update();
		void Clean();

		void Play(const Sound &sound, float gain = 1.f, float pitch = 1.f);

		SoundSourceID GetID() const {
			return m_ID;
		}

		ALID GetALID() const {
			return m_ALID;
		}

		bool IsActive() const {
			return m_Active;
		}

		void Deactivate();
	};
}