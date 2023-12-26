#include "ShaderProgram.h"

#include <filesystem>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <glad/glad.h>

#include "../../Debugging.h"

namespace Prisma::Graphics {
	ShaderProgram::ShaderProgram(ShaderProgramID id) : m_ID(id) {
	}

	void ShaderProgram::Load(const std::string &completeFolderPath) {
		// Ensuring that the provided folder path exists
		if (!std::filesystem::exists(completeFolderPath)) {
			Debugging::LogError("Attempting to load shaders from a non-existent folder path (\"" + completeFolderPath + "\")");
			return;
		}

		// Storing a pointer to the last folder in the path for later use
		std::filesystem::path FSFolderPath(completeFolderPath);

		auto FSFolderPathLast = FSFolderPath.end();
		FSFolderPathLast--;

		// Mapping file extensions to shader types
		std::unordered_map<std::string, int> extToShaderType = {
			{ ".vert", GL_VERTEX_SHADER },
			{ ".tesc", GL_TESS_CONTROL_SHADER },
			{ ".tese", GL_TESS_EVALUATION_SHADER },
			{ ".geom", GL_GEOMETRY_SHADER },
			{ ".frag", GL_FRAGMENT_SHADER }
		};

		// Accessing all the relevant files within the folder and creating shaders from them, storing the shader IDs
		std::vector<GLID> ShaderGLIDs;

		for (const auto &file : std::filesystem::directory_iterator(completeFolderPath)) {
			if (file.is_regular_file()) {
				std::string fileName = file.path().filename().stem().string();
				std::string extension = file.path().extension().string();

				if (fileName == FSFolderPathLast->string()) {
					// Reading the shader file and storing its contents
					std::ifstream fileStream;
					fileStream.open(completeFolderPath + '/' + fileName + extension);

					std::stringstream stringStream;
					stringStream << fileStream.rdbuf();

					fileStream.close();

					std::string sourceString = stringStream.str();
					const char *source = sourceString.c_str();

					// Creating the shader
					GLID shaderGLID = glCreateShader(extToShaderType[extension]);
					glShaderSource(shaderGLID, 1, &source, NULL);
					glCompileShader(shaderGLID);

					ShaderGLIDs.push_back(shaderGLID);
				}
			}
		}

		// Creating the program
		m_GLID = glCreateProgram();

		for (GLID shaderGLID : ShaderGLIDs) {
			glAttachShader(m_GLID, shaderGLID);
		}

		glLinkProgram(m_GLID);

		// Cleaning up
		for (GLID shaderGLID : ShaderGLIDs) {
			glDeleteShader(shaderGLID);
		}
	}

	void ShaderProgram::Clean() {
		glDeleteProgram(m_GLID);
	}
}