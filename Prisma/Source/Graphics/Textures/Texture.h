#pragma once

#include <string>

#include "../GLID.h"
#include "RGBAImageBuffer.h"
#include "../../Debugging.h"

namespace Prisma::Graphics {
	typedef unsigned short TextureID;

	class Texture {
		TextureID m_ID = 0;

		GLID m_GLID = 0;
		bool m_HasGLID = true;

		unsigned short m_Width = 0;
		unsigned short m_Height = 0;

		void GenerateGLTexture(unsigned char *buffer, bool linear);

	public:
		Texture(TextureID id, const std::string &filePathNoExt, bool linear = false);
		Texture(const RGBAImageBuffer &imageBuffer, bool linear = false);

		void Clean();

		TextureID GetID() const {
			return m_ID;
		}

		GLID GetGLID() const {
			return m_GLID;
		}

		unsigned short GetWidth() const {
			return m_Width;
		}

		unsigned short GetHeight() const {
			return m_Height;
		}
	};
}