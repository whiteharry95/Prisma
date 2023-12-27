#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <array>
#include <bitset>

#include "Sound.h"
#include "SoundSource.h"

namespace Prisma::Audio {
	class SoundManager {
		static constexpr unsigned char MaxSourceCount = 32;

		std::vector<Sound> m_Sounds;
		std::unordered_map<std::string, SoundID> m_SoundKeysToIDs;

		void AddSound(const std::string &filePathNoExt);

	public:
		void Init();
		void Clean();

		const Sound GetSound(SoundID id) const {
			return m_Sounds[id];
		}

		SoundID GetSoundID(const std::string &key) const {
			return m_SoundKeysToIDs.at(key);
		}
	};
}