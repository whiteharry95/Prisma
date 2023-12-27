#pragma once

#include <string>

#include "../ALID.h"

namespace Prisma::Audio {
	typedef unsigned char MusicID;

	class Music {
		MusicID m_ID;

		short *m_Buffer;

		unsigned char m_ChannelCount;
		unsigned int m_SampleCountPerChannel;
		unsigned int m_SampleRate;

	public:
		Music(MusicID id);

		void Load(const std::string &completeFilePath);
		void Clean();

		MusicID GetID() const {
			return m_ID;
		}

		const short *GetBuffer() const {
			return m_Buffer;
		}

		unsigned char GetChannelCount() const {
			return m_ChannelCount;
		}

		unsigned int GetSampleCountPerChannel() const {
			return m_SampleCountPerChannel;
		}

		unsigned int GetSampleRate() const {
			return m_SampleRate;
		}
	};
}