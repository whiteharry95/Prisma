#pragma once

#include <vector>
#include <unordered_map>
#include <string>

#include "ShaderProgram.h"

namespace Prisma::Graphics {
	class ShaderManager {
		std::vector<ShaderProgram> m_ShaderPrograms;
		std::unordered_map<std::string, ShaderProgramID> m_ShaderProgramKeysToIDs;

		void AddShaderProgram(const std::string &folderPath);

		ShaderManager(const ShaderManager &) = delete;

	public:
		ShaderManager() = default;

		void Init();
		void Clean();

		const ShaderProgram GetShaderProgram(ShaderProgramID id) const {
			return m_ShaderPrograms[id];
		}

		ShaderProgramID GetShaderProgram(const std::string &key) const {
			return m_ShaderProgramKeysToIDs.at(key);
		}
	};
}