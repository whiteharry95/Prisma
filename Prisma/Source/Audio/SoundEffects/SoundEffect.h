#pragma once

#include <string>
#include <audiofile/AudioFile.h>
#include <AL/al.h>

#include "../ALID.h"
#include "../../Debugging.h"

namespace Prisma::Audio {
	typedef unsigned short SoundEffectID;

	class SoundEffect {
		SoundEffectID m_ID;
		ALID m_BufferALID;

	public:
		SoundEffect(SoundEffectID id);

		template<typename T>
		void Load(const std::string &completeFilePath);

		void Clean();

		SoundEffectID GetID() const {
			return m_ID;
		}

		ALID GetBufferALID() const {
			return m_BufferALID;
		}
	};

	template<typename T>
	void SoundEffect::Load(const std::string &completeFilePath) {
		if (typeid(T) != typeid(unsigned char) && typeid(T) != typeid(short)) {
			return;
		}

		AudioFile<T> audioFile;
		audioFile.load(completeFilePath);

		if (audioFile.getBitDepth() == 8 && typeid(T) == typeid(short)) {
			Debugging::Log("Attempting to load an 8-bit audio file using a 16-bit type");
			return;
		}

		unsigned char channelCount = audioFile.getNumChannels();
		unsigned int sampleCountPerChannel = audioFile.getNumSamplesPerChannel();

		T *buffer = new T[channelCount * sampleCountPerChannel];

		for (int i = 0; i < channelCount * sampleCountPerChannel; i += channelCount) {
			buffer[i] = audioFile.samples[0][i / channelCount];

			if (channelCount == 2) {
				buffer[i + 1] = audioFile.samples[1][i / channelCount];
			}
		}

		int bufferFormat;

		if (typeid(T) == typeid(short)) {
			bufferFormat = channelCount == 2 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
		} else {
			bufferFormat = channelCount == 2 ? AL_FORMAT_STEREO8 : AL_FORMAT_MONO8;
		}

		alGenBuffers(1, &m_BufferALID);
		alBufferData(m_BufferALID, bufferFormat, buffer, channelCount * sampleCountPerChannel * sizeof(T), audioFile.getSampleRate());

		delete[] buffer;
	}
}