#include "Texture.h"

#include <glad/glad.h>
#include <stb/stb_image.h>

namespace Prisma::Graphics {
	void Texture::GenerateGLTexture(unsigned char *buffer, bool linear) {
		glGenTextures(1, &m_GLID);
		glBindTexture(GL_TEXTURE_2D, m_GLID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, linear ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, linear ? GL_LINEAR : GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	Texture::Texture(TextureID id) : m_ID(id) {
	}

	void Texture::Load(const std::string &completeFilePath, bool linear) {
		int imageWidth, imageHeight;
		unsigned char *imageBuffer = stbi_load(completeFilePath.c_str(), &imageWidth, &imageHeight, nullptr, 4);

		m_Width = imageWidth;
		m_Height = imageHeight;

		if (!imageBuffer) {
			Debugging::LogError("Failed to load image at file path \"" + completeFilePath + "\"");
			return;
		}

		GenerateGLTexture(imageBuffer, linear);
		stbi_image_free(imageBuffer);
	}

	void Texture::Load(const RGBAImageBuffer &rgbaImageBuffer, bool linear) {
		m_HasGLID = false;

		m_Width = rgbaImageBuffer.GetWidth();
		m_Height = rgbaImageBuffer.GetHeight();

		GenerateGLTexture(rgbaImageBuffer.GetRaw(), linear);
	}

	void Texture::Clean() {
		if (m_HasGLID) {
			glDeleteTextures(1, &m_GLID);
		}
	}
}