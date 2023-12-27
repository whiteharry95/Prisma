#include "SoundManager.h"

#include "../../Debugging.h"

namespace Prisma::Audio {
	void SoundManager::AddSound(const std::string &filePathNoExt) {
		SoundID id = static_cast<SoundID>(m_Sounds.size());

		m_Sounds.emplace_back(id, "Assets/Sounds/" + filePathNoExt + ".wav");
		m_SoundKeysToIDs[filePathNoExt] = id;
	}

	void SoundManager::Init() {
		AddSound("GunShot");
	}

	void SoundManager::Update() {
		for (auto &source : m_Sources) {
			source.Update();
		}
	}

	void SoundManager::Clean() {
		for (auto &sound : m_Sounds) {
			sound.Clean();
		}
	}

	const Sound SoundManager::GetSound(SoundID id) const {
		if (id < 0 || id >= m_Sounds.size()) {
			Debugging::LogError("Attempting to retrieve a sound of an out-of-bounds ID (" + std::to_string(id) + ")");
		}

		return m_Sounds[id];
	}

	SoundID SoundManager::GetSoundID(const std::string &key) const {
		if (m_SoundKeysToIDs.find(key) == m_SoundKeysToIDs.end()) {
			Debugging::LogError("Attempting to retrieve the ID of a non-existent sound");
		}

		return m_SoundKeysToIDs.at(key);
	}

	SoundSourceID SoundManager::AddSource(bool deactivateOnStop, bool loop) {
		for (int i = 0; i < m_Sources.size(); i++) {
			if (!m_Sources[i].IsActive()) {
				m_Sources[i].Clean();
				m_Sources[i] = SoundSource(i, deactivateOnStop, loop);

				return i;
			}
		}

		SoundSourceID id = static_cast<SoundSourceID>(m_Sources.size());
		m_Sources.emplace_back(id, deactivateOnStop, loop);
		return id;
	}

	void SoundManager::PlaySource(SoundSourceID id, SoundID soundID, float gain, float pitch) {
		m_Sources[id].Play(m_Sounds[soundID], gain, pitch);
	}
}