#pragma once

#include "../ALID.h"
#include "Sound.h"

namespace Prisma::Audio {
	typedef unsigned char SoundSourceID;

	class SoundSource {
		SoundSourceID m_ID;
		ALID m_ALID;

		bool m_Active = true;

		SoundID m_SoundID;

	public:
		SoundSource(SoundSourceID id);

		void Load(const Sound &sound);
		void Clean();

		void Play() const;
		void Stop() const;

		SoundSourceID GetID() const {
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

		SoundID GetSoundID() const {
			return m_SoundID;
		}
	};
}