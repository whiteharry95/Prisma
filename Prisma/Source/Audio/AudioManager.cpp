#include "AudioManager.h"

#include "../Debugging.h"

namespace Prisma::Audio {
	void AudioManager::AddSoundEffect(const std::string &filePathNoExt, bool is8Bit) {
		SoundEffectID id = m_SFX.size();

		SoundEffect soundEffect(id);
		std::string completeFilePath = "Assets/SoundEffects/" + filePathNoExt + ".wav";

		if (is8Bit) {
			soundEffect.Load<unsigned char>(completeFilePath);
		} else {
			soundEffect.Load<short>(completeFilePath);
		}

		m_SFX.push_back(soundEffect);
		m_SoundEffectKeysToIDs[filePathNoExt] = id;
	}

	void AudioManager::Init() {
		// Opening a playback device
		m_ALDevice = alcOpenDevice(nullptr);

		if (!m_ALDevice) {
			Debugging::Log("Failed to open a playback device for OpenAL");
			return;
		}

		// Creating an OpenAL context
		m_ALContext = alcCreateContext(m_ALDevice, nullptr);

		if (!m_ALContext) {
			Debugging::Log("Failed to create an OpenAL context");
			return;
		}

		alcMakeContextCurrent(m_ALContext);

		// Adding sound effects
		AddSoundEffect("Stinger");
	}

	void AudioManager::Clean() {
		for (SoundEffect &soundEffect : m_SFX) {
			soundEffect.Clean();
		}

		alcDestroyContext(m_ALContext);
		alcCloseDevice(m_ALDevice);
	}

	AudioSourceID AudioManager::AddSource(SoundEffectID soundEffectID) {
		AudioSourceID sourceID = m_Sources.size();

		if (!m_AvailableSourceIDs.empty()) {
			sourceID = m_AvailableSourceIDs.back();
			m_AvailableSourceIDs.pop_back();
		}

		AudioSource source(sourceID);
		source.Load(GetSoundEffect(soundEffectID));

		if (soundEffectID == m_Sources.size()) {
			m_Sources.push_back(source);
		} else {
			m_Sources[sourceID] = source;
		}

		return sourceID;
	}

	void AudioManager::RemoveSource(AudioSourceID sourceID) {
		m_Sources[sourceID].Stop();
		m_Sources[sourceID].Deactivate();

		m_AvailableSourceIDs.push_front(sourceID);
	}
}