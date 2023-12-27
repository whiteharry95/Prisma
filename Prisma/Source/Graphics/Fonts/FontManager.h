#pragma once

#include <vector>
#include <unordered_map>

#include "FontFace.h"
#include "Font.h"

namespace Prisma::Graphics {
	class FontManager {
		std::vector<FontFace> m_FontFaces;
		std::unordered_map<std::string, FontFaceID> m_FontFaceKeysToIDs;

		std::vector<Font> m_Fonts;
		std::unordered_map<std::string, FontID> m_FontKeysToIDs;

		const FontFace &AddFontFace(const std::string &filePathNoExt);
		void AddFont(const FontFace &face, unsigned short pointSize);

		FontManager(const FontManager &) = delete;

	public:
		FontManager() = default;

		void Init();
		void Clean();

		const FontFace GetFontFace(FontFaceID id) const {
			return m_FontFaces[id];
		}

		FontFaceID GetFontFaceID(const std::string &key) const {
			return m_FontFaceKeysToIDs.at(key);
		}

		const Font GetFont(FontID id) const {
			return m_Fonts[id];
		}

		FontID GetFontID(const std::string &key) const {
			return m_FontKeysToIDs.at(key);
		}
	};
}