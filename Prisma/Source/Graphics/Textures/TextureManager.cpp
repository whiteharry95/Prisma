#include "TextureManager.h"

namespace Prisma::Graphics {
	void TextureManager::AddTexture(const std::string &filePathNoExt) {
		TextureID id = m_Textures.size();

		Texture texture(id);
		texture.Load("Assets/Textures/" + filePathNoExt + ".png", false);

		m_Textures.push_back(texture);
		m_TextureKeysToIDs[filePathNoExt] = id;
	}

	void TextureManager::Init() {
		AddTexture("Player");
		AddTexture("Grass");
		AddTexture("Worms");
	}

	void TextureManager::Clean() {
		for (Texture &texture : m_Textures) {
			texture.Clean();
		}
	}
}