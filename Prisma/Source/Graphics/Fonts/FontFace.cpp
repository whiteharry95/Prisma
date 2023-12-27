#include "FontFace.h"

#include "../../Application.h"

namespace Prisma::Graphics {
	FontFace::FontFace(FontFaceID id, const std::string &key) : m_ID(id), m_Key(key) {
	}

	void FontFace::Load(const std::string &completeFilePath) {
		if (FT_New_Face(Application::Get().GetFTLibrary(), completeFilePath.c_str(), 0, &m_FTFace)) {
			Debugging::LogError("Failed to load font at file path \"" + completeFilePath + "\"");
		}
	}

	void FontFace::Clean() {
		FT_Done_Face(m_FTFace);
	}
}