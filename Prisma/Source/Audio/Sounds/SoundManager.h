#pragma once

#include <vector>
#include <unordered_map>

#include "Sound.h"
#include "SoundSource.h"

namespace Prisma::Audio {
	class SoundManager {
		std::vector<Sound> m_Sounds;
		std::unordered_map<std::string, SoundID> m_SoundKeysToIDs;

		std::vector<SoundSource> m_Sources;

		void AddSound(const std::string &filePathNoExt);

	public:
		void Init();
		void Update();
		void Clean();

		const Sound GetSound(SoundID id) const;
		SoundID GetSoundID(const std::string &key) const;

		SoundSourceID AddSource(bool deactivateOnStop = true, bool loop = false);
		void PlaySource(SoundSourceID id, SoundID soundID, float gain = 1.f, float pitch = 1.f);
	};
}