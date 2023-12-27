#pragma once

#include <vector>
#include <unordered_map>
#include <deque>

#include "Sound.h"
#include "SoundSource.h"

namespace Prisma::Audio {
	class SoundManager {
		std::vector<Sound> m_Sounds;
		std::unordered_map<std::string, SoundID> m_SoundKeysToIDs;

		std::vector<SoundSource> m_Sources;
		std::deque<SoundSourceID> m_AvailableSourceIDs;

		void AddSound(const std::string &filePathNoExt);

	public:
		void Init();
		void Clean();

		const Sound &GetSound(SoundID id) const {
			return m_Sounds[id];
		}

		SoundID GetSoundID(const std::string &key) const {
			return m_SoundKeysToIDs.at(key);
		}

		const SoundSource &GetSource(SoundSourceID id) const;
		SoundSourceID AddSource(SoundID soundID);
		void DeactivateSource(SoundSourceID id);
	};
}