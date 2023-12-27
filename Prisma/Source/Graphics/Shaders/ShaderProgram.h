#pragma once

#include <string>

#include "../GLID.h"

namespace Prisma::Graphics {
	typedef unsigned char ShaderProgramID;

	class ShaderProgram {
		ShaderProgramID m_ID = 0;
		GLID m_GLID = 0;

	public:
		ShaderProgram(ShaderProgramID id, const std::string &completeFolderPath);

		void Clean();

		ShaderProgramID GetID() const {
			return m_ID;
		}

		GLID GetGLID() const {
			return m_GLID;
		}
	};
}