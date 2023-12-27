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
		for (Sound &sound : m_Sounds) {
			sound.Clean();
		}
	}

	const SoundSource &SoundManager::GetSource(SoundSourceID id) const {
		if (!m_Sources[id].IsActive()) {
			Debugging::LogWarning("Retrieving an inactive sound source");
		}

		return m_Sources[id];
	}

	SoundSourceID SoundManager::AddSource(SoundID soundID) {
		SoundSourceID id = m_Sources.size();

		if (!m_AvailableSourceIDs.empty()) {
			id = m_AvailableSourceIDs.back();
			m_AvailableSourceIDs.pop_back();
		}

		SoundSource source(id);
		source.Load(GetSound(soundID));

		if (soundID == m_Sources.size()) {
			m_Sources.push_back(source);
		} else {
			m_Sources[id].Clean();
			m_Sources[id] = source;
		}

		return id;
	}

	void SoundManager::DeactivateSource(SoundSourceID id) {
		if (!m_Sources[id].IsActive()) {
			Debugging::LogWarning("Attempting to deactivate a sound source that has already been removed");
			return;
		}

		m_Sources[id].Deactivate();
		m_AvailableSourceIDs.push_front(id);
	}
}