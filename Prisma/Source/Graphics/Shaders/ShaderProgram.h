#pragma once

#include <string>

#include "../GLID.h"

namespace Prisma::Graphics {
	typedef unsigned char ShaderProgramID;

	class ShaderProgram {
		ShaderProgramID m_ID;
		GLID m_GLID;

	public:
		ShaderProgram(ShaderProgramID id);

		void Load(const std::string &completeFolderPath);
		void Clean();

		ShaderProgramID GetID() const {
			return m_ID;
		}

		GLID GetGLID() const {
			return m_GLID;
		}
	};
}