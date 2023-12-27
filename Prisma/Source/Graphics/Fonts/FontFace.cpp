#include "FontFace.h"

#include "../../Application.h"

namespace Prisma::Graphics {
	FontFace::FontFace(FontFaceID id, const std::string &key, const std::string &completeFilePath) : m_ID(id), m_Key(key) {
		if (FT_New_Face(Application::Get().GetFTLibrary(), completeFilePath.c_str(), 0, &m_FTFace)) {
			Debugging::LogError("Failed to load font at file path \"" + completeFilePath + "\"");
		}
	}

	void FontFace::Clean() {
		FT_Done_Face(m_FTFace);
	}
}