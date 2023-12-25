#pragma once

#include <vector>
#include <deque>
#include <AL/al.h>
#include <AL/alc.h>

#include "SoundEffects/SoundEffect.h"
#include "AudioSource.h"

namespace Prisma::Audio {
	class AudioManager {
		ALCdevice *m_ALDevice;
		ALCcontext *m_ALContext;

		std::vector<SoundEffect> m_SFX;
		std::unordered_map<std::string, SoundEffectID> m_SoundEffectKeysToIDs;

		std::vector<AudioSource> m_Sources;
		std::deque<AudioSourceID> m_AvailableSourceIDs;

		void AddSoundEffect(const std::string &filePathNoExt, bool is8Bit = false);

	public:
		void Init();
		void Clean();

		const SoundEffect &GetSoundEffect(SoundEffectID id) const {
			return m_SFX[id];
		}

		SoundEffectID GetSoundEffectID(const std::string &key) const {
			return m_SoundEffectKeysToIDs.at(key);
		}

		const AudioSource &GetSource(AudioSourceID id) const {
			return m_Sources[id];
		}

		AudioSourceID AddSource(SoundEffectID soundEffectID);
		void RemoveSource(AudioSourceID sourceID);
	};
}