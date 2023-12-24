#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>

namespace Prisma::Graphics {
	typedef unsigned char FontFaceID;

	class FontFace {
		FontFaceID m_ID;
		std::string m_Key;

		FT_Face m_FTFace;

	public:
		static constexpr unsigned short DPI = 96;

		FontFace(FontFaceID id, const std::string &key);

		void Load(const std::string &completeFilePath);
		void Clean();

		FontFaceID GetID() const {
			return m_ID;
		}

		const std::string &GetKey() const {
			return m_Key;
		}

		FT_Face GetFTFace() const {
			return m_FTFace;
		}
	};
}