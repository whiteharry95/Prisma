#include "FontManager.h"

namespace Prisma::Graphics {
	const FontFace &FontManager::AddFontFace(const std::string &filePathNoExt) {
		FontFaceID id = static_cast<FontFaceID>(m_FontFaces.size());

		m_FontFaces.emplace_back(id, filePathNoExt, "Assets/Fonts/" + filePathNoExt + ".ttf");
		m_FontFaceKeysToIDs[filePathNoExt] = id;

		return m_FontFaces[id];
	}

	void FontManager::AddFont(const FontFace &face, unsigned short pointSize) {
		FontID id = static_cast<FontID>(m_Fonts.size());

		m_Fonts.emplace_back(id, face, pointSize);
		m_FontKeysToIDs[face.GetKey() + std::to_string(pointSize)] = id;
	}

	void FontManager::Init() {
		const FontFace &arial = AddFontFace("Arial");

		AddFont(arial, 18);
		AddFont(arial, 24);
	}

	void FontManager::Clean() {
		for (Font &font : m_Fonts) {
			font.Clean();
		}

		for (FontFace &fontFace : m_FontFaces) {
			fontFace.Clean();
		}
	}
}