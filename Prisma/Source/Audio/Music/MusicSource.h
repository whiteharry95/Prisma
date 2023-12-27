#pragma once

#include "Music.h"
#include "../ALID.h"

namespace Prisma::Audio {
	typedef unsigned char MusicSourceID;

	class MusicManager;

	class MusicSource {
		static constexpr unsigned int BufferCount = 4;
		static constexpr unsigned int SampleCountPerBuffer = 44100;

		MusicSourceID m_ID = 0;
		ALID m_ALID = 0;

		ALID m_BufferALIDs[BufferCount] = { };
		unsigned int m_QueuedBufferCounter = 0;

		bool m_Active = true;

		MusicID m_MusicID = 0;

	public:
		MusicSource(MusicSourceID id, const Music &music);

		void Update(const MusicManager &musicManager);
		void Clean();

		void Play(const MusicManager &musicManager);

		MusicSourceID GetID() const {
			return m_ID;
		}

		ALID GetALID() const {
			return m_ALID;
		}

		bool IsActive() const {
			return m_Active;
		}

		void Deactivate();

		MusicID GetMusicID() const {
			return m_MusicID;
		}
	};
}