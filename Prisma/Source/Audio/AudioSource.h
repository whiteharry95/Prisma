#pragma once

#include "SoundEffects/SoundEffect.h"
#include "ALID.h"

namespace Prisma::Audio {
	typedef unsigned char AudioSourceID;

	class AudioSource {
		AudioSourceID m_ID;
		ALID m_ALID;

		bool m_Active = true;

		SoundEffectID m_SoundEffectID;

	public:
		AudioSource(AudioSourceID id);

		void Load(const SoundEffect &soundEffect);
		void Clean();

		void Play() const;
		void Stop() const;

		AudioSourceID GetID() const {
			return m_ID;
		}

		ALID GetALID() const {
			return m_ALID;
		}

		bool GetActive() const {
			return m_Active;
		}

		void Deactivate() {
			m_Active = false;
		}

		SoundEffectID GetSoundEffectID() const {
			return m_SoundEffectID;
		}
	};
}