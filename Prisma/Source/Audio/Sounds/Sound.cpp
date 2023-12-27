#include "Sound.h"

#include <audiofile/AudioFile.h>
#include <AL/al.h>

#include "../../Debugging.h"

namespace Prisma::Audio {
	Sound::Sound(SoundID id) : m_ID(id) {
	}

	void Sound::Load(const std::string &completeFilePath) {
		// Loading the audio file
		AudioFile<short> audioFile;

		if (!audioFile.load(completeFilePath)) {
			return;
		}

		unsigned char channelCount = audioFile.getNumChannels();
		unsigned int sampleCountPerChannel = audioFile.getNumSamplesPerChannel();

		// Creating the buffer
		short *buffer = new short[sampleCountPerChannel * channelCount];

		for (int i = 0; i < sampleCountPerChannel * channelCount; i += channelCount) {
			buffer[i] = audioFile.samples[0][i / channelCount];

			if (channelCount == 2) {
				buffer[i + 1] = audioFile.samples[1][i / channelCount];
			}
		}

		// Generating the OpenAL buffer and giving it data
		alGenBuffers(1, &m_BufferALID);
		alBufferData(m_BufferALID, channelCount == 2 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16, buffer, channelCount * sampleCountPerChannel * sizeof(short), audioFile.getSampleRate());

		// Deleting the created buffer
		delete[] buffer;
	}

	void Sound::Clean() {
		alDeleteBuffers(1, &m_BufferALID);
	}
}