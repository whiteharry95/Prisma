#include "ShaderManager.h"

namespace Prisma::Graphics {
	void ShaderManager::AddShaderProgram(const std::string &folderPath) {
		ShaderProgramID id = m_ShaderPrograms.size();

		m_ShaderPrograms.emplace_back(id, "Assets/Shaders/" + folderPath);
		m_ShaderProgramKeysToIDs[folderPath] = id;
	}

	void ShaderManager::Init() {
		AddShaderProgram("Texture");
	}

	void ShaderManager::Clean() {
		for (ShaderProgram &shaderProgram : m_ShaderPrograms) {
			shaderProgram.Clean();
		}
	}
}