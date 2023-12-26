#pragma once

#include "Music.h"
#include "../ALID.h"

namespace Prisma::Audio {
	typedef unsigned char MusicSourceID;

	class MusicSource {
		MusicSourceID m_ID;
		ALID m_ALID;

		bool m_Active = true;

		MusicID m_MusicID;

	public:
		MusicSource(MusicSourceID id);

		void Load(const Music &music);
		void Clean();

		void Play() const;
		void Stop() const;

		MusicSourceID GetID() const {
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

		MusicID GetMusicID() const {
			return m_MusicID;
		}
	};
}