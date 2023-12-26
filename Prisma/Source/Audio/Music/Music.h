#pragma once

#include <string>

#include "../ALID.h"

namespace Prisma::Audio {
	typedef unsigned char MusicID;

	class Music {
	public:
		static constexpr unsigned char BufferCount = 4;

	private:
		static constexpr unsigned short SampleCountPerBuffer = 8192;

		MusicID m_ID;
		ALID m_BufferALIDs[BufferCount];

	public:
		Music(MusicID id);

		template<typename T>
		void Load(const std::string &completeFilePath);

		void Clean();

		MusicID GetID() const {
			return m_ID;
		}
	};

	template<typename T>
	void Music::Load(const std::string &completeFilePath) {
		// Loading the audio file
		AudioFile<T> audioFile;
		audioFile.load(completeFilePath);

		unsigned char channelCount = audioFile.getNumChannels();
		unsigned int sampleCountPerChannel = audioFile.getNumSamplesPerChannel();

		// Generating the OpenAL buffers
		alGenBuffers(BufferCount, m_BufferALIDs);

		// Determining the buffer format
		int bufferFormat;

		if (typeid(T) == typeid(short)) {
			bufferFormat = channelCount == 2 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
		} else {
			bufferFormat = channelCount == 2 ? AL_FORMAT_STEREO8 : AL_FORMAT_MONO8;
		}

		// Giving data to the buffers
		for (int i = 0; i < BufferCount; i++) {
			T buffer[SampleCountPerBuffer];

			for (int j = 0; j < SampleCountPerBuffer; j += channelCount) {
				buffer[j] = audioFile.samples[0][((i * SampleCountPerBuffer) + j) / channelCount];

				if (channelCount == 2) {
					buffer[j + 1] = audioFile.samples[1][((i * SampleCountPerBuffer) + j) / channelCount];
				}
			}

			alBufferData(m_BufferALIDs[i], bufferFormat, buffer, SampleCountPerBuffer * sizeof(T), audioFile.getSampleRate());
		}
	}
}