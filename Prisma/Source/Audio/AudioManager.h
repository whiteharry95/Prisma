#pragma once

#include <vector>
#include <deque>
#include <AL/al.h>
#include <AL/alc.h>

#include "Sounds/Sound.h"
#include "Sounds/SoundSource.h"

namespace Prisma::Audio {
	class AudioManager {
		ALCdevice *m_ALDevice;
		ALCcontext *m_ALContext;

		std::vector<Sound> m_Sounds;
		std::unordered_map<std::string, SoundID> m_SoundKeysToIDs;

		std::vector<SoundSource> m_SoundSources;
		std::deque<SoundSourceID> m_AvailableSoundSourceIDs;

		void AddSound(const std::string &filePathNoExt, bool is8Bit = false);

	public:
		void Init();
		void Clean();

		const Sound &GetSound(SoundID id) const {
			return m_Sounds[id];
		}

		SoundID GetSoundID(const std::string &key) const {
			return m_SoundKeysToIDs.at(key);
		}

		const SoundSource &GetSoundSource(SoundSourceID id) const {
			return m_SoundSources[id];
		}

		SoundSourceID AddSoundSource(SoundID soundID);
		void RemoveSoundSource(SoundSourceID id);
	};
}