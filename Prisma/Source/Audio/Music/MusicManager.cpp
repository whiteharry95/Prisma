#include "MusicManager.h"

namespace Prisma::Audio {
	void MusicManager::AddMusic(const std::string &filePathNoExt) {
		MusicID id = m_Music.size();

		Music music(id);
		music.Load("Assets/Music/" + filePathNoExt + ".wav");

		m_Music.push_back(music);
		m_MusicKeysToIDs[filePathNoExt] = id;
	}

	void MusicManager::Init() {
		AddMusic("Cold");
		AddMusic("Piano");

		MusicSourceID sourceID = AddMusicSource(GetMusicID("Piano"));
		m_MusicSources[sourceID].Play(*this);
	}

	void MusicManager::Update() {
		for (MusicSource &source : m_MusicSources) {
			if (source.GetActive()) {
				source.Update(*this);
			}
		}
	}

	void MusicManager::Clean() {
		for (Music &music : m_Music) {
			music.Clean();
		}
	}

	MusicSourceID MusicManager::AddMusicSource(MusicID musicID) {
		MusicSourceID id = m_MusicSources.size();

		if (!m_AvailableMusicSourceIDs.empty()) {
			id = m_AvailableMusicSourceIDs.back();
			m_AvailableMusicSourceIDs.pop_back();
		}

		MusicSource source(id);
		source.Load(GetMusic(musicID));

		if (id == m_MusicSources.size()) {
			m_MusicSources.push_back(source);
		} else {
			m_MusicSources[id].Clean();
			m_MusicSources[id] = source;
		}

		return id;
	}

	void MusicManager::RemoveMusicSource(MusicSourceID id) {
		m_MusicSources[id].Stop();
		m_MusicSources[id].Deactivate();

		m_AvailableMusicSourceIDs.push_front(id);
	}
}