#include "AudioManager.h"

#include "../Debugging.h"

namespace Prisma::Audio {
	void AudioManager::AddSound(const std::string &filePathNoExt, bool is8Bit) {
		SoundID id = m_Sounds.size();

		Sound sound(id);
		std::string completeFilePath = "Assets/Sounds/" + filePathNoExt + ".wav";

		if (is8Bit) {
			sound.Load<unsigned char>(completeFilePath);
		} else {
			sound.Load<short>(completeFilePath);
		}

		m_Sounds.push_back(sound);
		m_SoundKeysToIDs[filePathNoExt] = id;
	}

	void AudioManager::Init() {
		// Opening a playback device
		m_ALDevice = alcOpenDevice(nullptr);

		if (!m_ALDevice) {
			Debugging::LogError("Failed to open a playback device for OpenAL");
			return;
		}

		// Creating an OpenAL context
		m_ALContext = alcCreateContext(m_ALDevice, nullptr);

		if (!m_ALContext) {
			Debugging::LogError("Failed to create an OpenAL context");
			return;
		}

		alcMakeContextCurrent(m_ALContext);

		// Adding sounds
		AddSound("Desert");
	}

	void AudioManager::Clean() {
		for (Sound &sound : m_Sounds) {
			sound.Clean();
		}

		alcDestroyContext(m_ALContext);
		alcCloseDevice(m_ALDevice);
	}

	SoundSourceID AudioManager::AddSoundSource(SoundID soundID) {
		SoundSourceID id = m_SoundSources.size();

		if (!m_AvailableSoundSourceIDs.empty()) {
			id = m_AvailableSoundSourceIDs.back();
			m_AvailableSoundSourceIDs.pop_back();
		}

		SoundSource source(id);
		source.Load(GetSound(soundID));

		if (soundID == m_SoundSources.size()) {
			m_SoundSources.push_back(source);
		} else {
			m_SoundSources[id] = source;
		}

		return id;
	}

	void AudioManager::RemoveSoundSource(SoundSourceID id) {
		m_SoundSources[id].Stop();
		m_SoundSources[id].Deactivate();

		m_AvailableSoundSourceIDs.push_front(id);
	}
}