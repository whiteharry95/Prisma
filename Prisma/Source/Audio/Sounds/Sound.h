#pragma once

#include <string>
#include <audiofile/AudioFile.h>
#include <AL/al.h>

#include "../ALID.h"
#include "../../Debugging.h"

namespace Prisma::Audio {
	typedef unsigned short SoundID;

	class Sound {
		SoundID m_ID;
		ALID m_BufferALID;

	public:
		Sound(SoundID id);

		template<typename T>
		void Load(const std::string &completeFilePath);

		void Clean();

		SoundID GetID() const {
			return m_ID;
		}

		ALID GetBufferALID() const {
			return m_BufferALID;
		}
	};

	template<typename T>
	void Sound::Load(const std::string &completeFilePath) {
		if (typeid(T) != typeid(unsigned char) && typeid(T) != typeid(short)) {
			Debugging::LogError("Attempting to load audio using an invalid type");
			return;
		}

		// Loading the audio file
		AudioFile<T> audioFile;
		audioFile.load(completeFilePath);

		if (audioFile.getBitDepth() == 8 && typeid(T) == typeid(short)) {
			Debugging::LogError("Attempting to load an 8-bit audio file using a 16-bit type");
			return;
		}

		audioFile.printSummary();

		unsigned char channelCount = audioFile.getNumChannels();
		unsigned int sampleCountPerChannel = audioFile.getNumSamplesPerChannel();

		// Creating the buffer
		T *buffer = new T[channelCount * sampleCountPerChannel];

		for (int i = 0; i < channelCount * sampleCountPerChannel; i += channelCount) {
			buffer[i] = audioFile.samples[0][i / channelCount];

			if (channelCount == 2) {
				buffer[i + 1] = audioFile.samples[1][i / channelCount];
			}
		}

		// Determining the buffer format
		int bufferFormat;

		if (typeid(T) == typeid(short)) {
			bufferFormat = channelCount == 2 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
		} else {
			bufferFormat = channelCount == 2 ? AL_FORMAT_STEREO8 : AL_FORMAT_MONO8;
		}

		// Generating the OpenAL buffer and giving it data
		alGenBuffers(1, &m_BufferALID);
		alBufferData(m_BufferALID, bufferFormat, buffer, channelCount * sampleCountPerChannel * sizeof(T), audioFile.getSampleRate());

		delete[] buffer;
	}
}