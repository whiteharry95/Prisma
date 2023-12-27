#include "MusicManager.h"

#include "../../Debugging.h"

namespace Prisma::Audio {
	void MusicManager::AddMusic(const std::string &filePathNoExt) {
		MusicID id = static_cast<MusicID>(m_Music.size());

		m_Music.emplace_back(id, "Assets/Music/" + filePathNoExt + ".wav");
		m_MusicKeysToIDs[filePathNoExt] = id;
	}

	void MusicManager::Init() {
		AddMusic("Cold");
	}

	void MusicManager::Update() {
		for (auto &source : m_Sources) {
			source.Update(*this);
		}
	}

	void MusicManager::Clean() {
		for (auto &music : m_Music) {
			music.Clean();
		}
	}

	const Music &MusicManager::GetMusic(MusicID id) const {
		if (id < 0 || id >= m_Music.size()) {
			Debugging::LogError("Attempting to retrieve music of an out-of-bounds ID (" + std::to_string(id) + ")");
		}

		return m_Music[id];
	}

	MusicID MusicManager::GetMusicID(const std::string &key) const {
		if (m_MusicKeysToIDs.find(key) == m_MusicKeysToIDs.end()) {
			Debugging::LogError("Attempting to retrieve the ID of non-existent music");
		}

		return m_MusicKeysToIDs.at(key);
	}

	MusicSourceID MusicManager::AddSource(MusicID musicID) {
		for (int i = 0; i < m_Sources.size(); i++) {
			if (!m_Sources[i].IsActive()) {
				m_Sources[i].Clean();
				m_Sources[i] = MusicSource(i, GetMusic(musicID));

				return i;
			}
		}

		MusicSourceID id = static_cast<MusicSourceID>(m_Sources.size());
		m_Sources.emplace_back(id, GetMusic(musicID));
		return id;
	}

	void MusicManager::PlaySource(MusicSourceID id) {
		m_Sources[id].Play(*this);
	}
}