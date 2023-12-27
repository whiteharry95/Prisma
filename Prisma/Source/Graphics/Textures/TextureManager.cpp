#include "TextureManager.h"

namespace Prisma::Graphics {
	void TextureManager::AddTexture(const std::string &filePathNoExt) {
		TextureID id = m_Textures.size();

		m_Textures.emplace_back(id, "Assets/Textures/" + filePathNoExt + ".png", false);
		m_TextureKeysToIDs[filePathNoExt] = id;
	}

	void TextureManager::Init() {
		AddTexture("Player");
	}

	void TextureManager::Clean() {
		for (Texture &texture : m_Textures) {
			texture.Clean();
		}
	}
}