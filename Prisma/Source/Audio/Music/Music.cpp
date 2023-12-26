#include "Music.h"

#include <audiofile/AudioFile.h>
#include <AL/al.h>

#include "../../Debugging.h"

namespace Prisma::Audio {
	void Music::Clean() {
		alDeleteBuffers(BufferCount, m_BufferALIDs);
		delete[] m_BufferALIDs;
	}
}