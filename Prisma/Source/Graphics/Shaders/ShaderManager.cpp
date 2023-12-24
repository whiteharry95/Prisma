#include "ShaderManager.h"

namespace Prisma::Graphics {
	void ShaderManager::AddShaderProgram(const std::string &folderPath) {
		ShaderProgramID id = m_ShaderPrograms.size();

		ShaderProgram program(id);
		program.Load("Assets/Shaders/" + folderPath);

		m_ShaderPrograms.push_back(program);
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