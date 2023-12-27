#pragma once

#include <vector>
#include <unordered_map>

#include "Music.h"
#include "MusicSource.h"

namespace Prisma::Audio {
	class MusicManager {
		std::vector<Music> m_Music;
		std::unordered_map<std::string, MusicID> m_MusicKeysToIDs;

		std::vector<MusicSource> m_Sources;

		void AddMusic(const std::string &filePathNoExt);

	public:
		void Init();
		void Update();
		void Clean();

		const Music &GetMusic(MusicID id) const;
		MusicID GetMusicID(const std::string &key) const;

		MusicSourceID AddSource(MusicID musicID);
		void PlaySource(MusicSourceID id);
	};
}