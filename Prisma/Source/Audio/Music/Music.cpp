#include "Music.h"

#include <audiofile/AudioFile.h>
#include <AL/al.h>

namespace Prisma::Audio {
	Music::Music(MusicID id, const std::string &completeFilePath) : m_ID(id) {
		// Loading the audio file
		AudioFile<short> audioFile;
		audioFile.load(completeFilePath);

		m_ChannelCount = audioFile.getNumChannels();
		m_SampleCountPerChannel = audioFile.getNumSamplesPerChannel();
		m_SampleRate = audioFile.getSampleRate();

		// Creating the buffer
		m_Buffer = new short[m_SampleCountPerChannel * m_ChannelCount];

		for (int i = 0; i < m_SampleCountPerChannel * m_ChannelCount; i += m_ChannelCount) {
			m_Buffer[i] = audioFile.samples[0][i / m_ChannelCount];

			if (m_ChannelCount == 2) {
				m_Buffer[i + 1] = audioFile.samples[1][i / m_ChannelCount];
			}
		}
	}

	void Music::Clean() {
		delete[] m_Buffer;
	}
}