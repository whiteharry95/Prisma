#pragma once

#include <vector>
#include <unordered_map>
#include <deque>

#include "Music.h"
#include "MusicSource.h"

namespace Prisma::Audio {
	class MusicManager {
		std::vector<Music> m_Music;
		std::unordered_map<std::string, MusicID> m_MusicKeysToIDs;

		std::vector<MusicSource> m_MusicSources;
		std::deque<MusicSourceID> m_AvailableMusicSourceIDs;

		void AddMusic(const std::string &filePathNoExt);

	public:
		void Init();
		void Update();
		void Clean();

		const Music &GetMusic(MusicID id) const {
			return m_Music[id];
		}

		MusicID GetMusicID(const std::string &key) const {
			return m_MusicKeysToIDs.at(key);
		}

		const MusicSource &GetMusicSource(MusicSourceID id) const {
			return m_MusicSources[id];
		}

		MusicSourceID AddMusicSource(MusicID musicID);
		void RemoveMusicSource(MusicSourceID id);
	};
}