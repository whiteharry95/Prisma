#include "FontManager.h"

namespace Prisma::Graphics {
	const FontFace &FontManager::AddFontFace(const std::string &filePathNoExt) {
		FontFaceID id = m_FontFaces.size();

		FontFace face(id, filePathNoExt);
		face.Load("Assets/Fonts/" + filePathNoExt + ".ttf");

		m_FontFaces.push_back(face);
		m_FontFaceKeysToIDs[filePathNoExt] = id;

		return m_FontFaces[id];
	}

	void FontManager::AddFont(const FontFace &face, unsigned short pointSize) {
		FontID id = m_Fonts.size();

		Font font(id);
		font.Load(face, pointSize);

		m_Fonts.push_back(font);
		m_FontKeysToIDs[face.GetKey() + std::to_string(pointSize)] = id;
	}

	void FontManager::Init() {
		const FontFace &arial = AddFontFace("Arial");

		AddFont(arial, 18);
		AddFont(arial, 24);

		const FontFace &consolas = AddFontFace("Consolas");

		AddFont(consolas, 36);
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