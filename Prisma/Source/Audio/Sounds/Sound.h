#pragma once

#include <string>

#include "../ALID.h"

namespace Prisma::Audio {
	typedef unsigned short SoundID;

	class Sound {
		SoundID m_ID;
		ALID m_BufferALID;

	public:
		Sound(SoundID id);

		void Load(const std::string &completeFilePath);
		void Clean();

		SoundID GetID() const {
			return m_ID;
		}

		ALID GetBufferALID() const {
			return m_BufferALID;
		}
	};
}