#include "SoundManager.h"

#include "../../Debugging.h"

namespace Prisma::Audio {
	void SoundManager::AddSound(const std::string &filePathNoExt) {
		SoundID id = m_Sounds.size();

		Sound sound(id);
		sound.Load("Assets/Sounds/" + filePathNoExt + ".wav");

		m_Sounds.push_back(sound);
		m_SoundKeysToIDs[filePathNoExt] = id;
	}

	void SoundManager::Init() {
		AddSound("Stinger");
	}

	void SoundManager::Clean() {
		for (auto &sound : m_Sounds) {
			sound.Clean();
		}
	}

	const SoundSource SoundManager::GetSource(SoundSourceID id) const {
		if (!m_ActiveSources[id]) {
			Debugging::LogWarning("Attempting to retrieve an inactive sound source");
			return NULL;
		}

		return m_Sources[id];
	}

	SoundSourceID SoundManager::AddSource(SoundID soundID) {
		SoundSourceID id;

		for (int i = 0; i < m_Sources.size(); i++) {
			if (!m_ActiveSources[i]) {
				if (m_Sources[i].IsLoaded()) {
					m_Sources[i].Clean();
				}

				SoundSource source(id);
				source.Init(GetSound(soundID));
			}
		}

		return id;
	}

	void SoundManager::DeactivateSource(SoundSourceID id) {
		if (!m_Sources[id].IsActive()) {
			Debugging::LogWarning("Attempting to deactivate a sound source that is already inactive");
			return;
		}

		m_Sources[id].Deactivate();
		m_AvailableSourceIDs.push_front(id);
	}
}