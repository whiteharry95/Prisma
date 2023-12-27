#include "MusicSource.h"
#include "MusicManager.h"

#include <AL/al.h>

#include "../../Debugging.h"

namespace Prisma::Audio {
	MusicSource::MusicSource(MusicSourceID id, const Music &music) : m_ID(id), m_MusicID(music.GetID()) {
		alGenBuffers(BufferCount, m_BufferALIDs);
		alGenSources(1, &m_ALID);
	}

	void MusicSource::Update(const MusicManager &musicManager) {
		if (!m_Active) {
			return;
		}

		const Music &music = musicManager.GetMusic(m_MusicID);
		const short *musicBuffer = music.GetBuffer();

		// Checking for processed buffers
		int processedBufferCount;
		alGetSourcei(m_ALID, AL_BUFFERS_PROCESSED, &processedBufferCount);

		while (processedBufferCount > 0) {
			// Unqueuing the buffer
			ALID bufferID;
			alSourceUnqueueBuffers(m_ALID, 1, &bufferID);

			// Looping
			if (SampleCountPerBuffer * (m_QueuedBufferCounter + 1) > music.GetSampleCountPerChannel() * music.GetChannelCount()) {
				m_QueuedBufferCounter = 0;
			}

			// Creating the buffer
			short *buffer = new short[SampleCountPerBuffer];

			for (int j = 0; j < SampleCountPerBuffer; j++) {
				buffer[j] = musicBuffer[(m_QueuedBufferCounter * SampleCountPerBuffer) + j];
			}

			alBufferData(bufferID, music.GetChannelCount() == 2 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16, buffer, SampleCountPerBuffer * sizeof(short), music.GetSampleRate());

			delete[] buffer;

			// Queuing the buffer
			alSourceQueueBuffers(m_ALID, 1, &bufferID);
			m_QueuedBufferCounter++;

			processedBufferCount--;
		}
	}

	void MusicSource::Clean() {
		alDeleteSources(1, &m_ALID);
		alDeleteBuffers(BufferCount, m_BufferALIDs);
	}

	void MusicSource::Play(const MusicManager &musicManager) {
		if (!m_Active) {
			Debugging::LogWarning("Attempting to play an inactive music source");
			return;
		}

		alSourceRewind(m_ALID);

		const Music &music = musicManager.GetMusic(m_MusicID);
		const short *musicBuffer = music.GetBuffer();

		m_QueuedBufferCounter = 0;

		for (int i = 0; i < BufferCount; i++) {
			short *buffer = new short[SampleCountPerBuffer];

			for (int j = 0; j < SampleCountPerBuffer; j++) {
				buffer[j] = musicBuffer[(i * SampleCountPerBuffer) + j];
			}

			alBufferData(m_BufferALIDs[i], music.GetChannelCount() == 2 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16, buffer, SampleCountPerBuffer * sizeof(short), music.GetSampleRate());

			delete[] buffer;
		}

		alSourceQueueBuffers(m_ALID, BufferCount, m_BufferALIDs);
		m_QueuedBufferCounter += BufferCount;

		alSourcePlay(m_ALID);
	}

	void MusicSource::Deactivate() {
		alSourceStop(m_ALID);
		m_Active = false;
	}
}