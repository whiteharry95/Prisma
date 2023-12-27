#pragma once

#include <vector>
#include <unordered_map>
#include <string>

#include "Texture.h"

namespace Prisma::Graphics {
	class TextureManager {
		std::vector<Texture> m_Textures;
		std::unordered_map<std::string, TextureID> m_TextureKeysToIDs;

		void AddTexture(const std::string &filePathNoExt);

		TextureManager(const TextureManager &) = delete;

	public:
		TextureManager() = default;

		void Init();
		void Clean();

		const Texture GetTexture(TextureID id) const {
			return m_Textures[id];
		}

		TextureID GetTextureID(const std::string &key) const {
			return m_TextureKeysToIDs.at(key);
		}
	};
}