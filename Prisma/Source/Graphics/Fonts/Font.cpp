#include "Font.h"

#include <glad/glad.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "../../Application.h"
#include "FontFace.h"
#include "../Textures/RGBAImageBuffer.h"

namespace Prisma::Graphics {
	Font::Font(FontID id) : m_ID(id) {
	}

	void Font::Load(const FontFace &face, unsigned short pointSize) {
		m_FaceID = face.GetID();
		m_PointSize = pointSize;

		// Preparing the font face
		FT_Face ftFace = face.GetFTFace();
		FT_Set_Char_Size(ftFace, pointSize << 6, 0, FontFace::DPI, 0);

		// Creating and clearing an image buffer
		unsigned short height = (ftFace->size->metrics.height * 12) >> 6;
		unsigned short width = (height * 4) / 3;

		RGBAImageBuffer imageBuffer(width, height);
		imageBuffer.ClearPixels({ 255, 255, 255, 0 });

		// Adding characters to the texture
		short drawX = 0;
		short drawY = 0;

		short drawXAdvanceOffset = 5;

		unsigned int glyphIndexPrevious;

		for (char c = CharacterRangeStart; c <= CharacterRangeEnd; c++) {
			unsigned int glyphIndex = FT_Get_Char_Index(ftFace, c);

			FT_Load_Glyph(ftFace, glyphIndex, FT_LOAD_DEFAULT);
			FT_Render_Glyph(ftFace->glyph, FT_RENDER_MODE_NORMAL);

			if (drawX + ftFace->glyph->bitmap.width >= width) {
				drawX = 0;
				drawY += ftFace->size->metrics.height >> 6;

				if (drawY + ftFace->glyph->bitmap.rows >= height) {
					break;
				}
			}

			short drawXOffset = ftFace->glyph->bitmap_left;
			short drawYOffset = (height / 5) - ftFace->glyph->bitmap_top;

			SourceRectangle characterSourceRect = {
				drawX + drawXOffset, drawY + drawYOffset,
				ftFace->glyph->bitmap.width, ftFace->glyph->bitmap.rows + 1
			};

			m_CharacterSourceRects[c - CharacterRangeStart] = characterSourceRect;

			for (int y = 0; y < ftFace->glyph->bitmap.rows; y++) {
				for (int x = 0; x < ftFace->glyph->bitmap.width; x++) {
					unsigned char alpha = ftFace->glyph->bitmap.buffer[(y * ftFace->glyph->bitmap.width) + x];

					if (alpha > 0) {
						imageBuffer.SetPixel(drawX + drawXOffset + x, drawY + drawYOffset + y, { 255, 255, 255, alpha });
					}
				}
			}

			drawX += (ftFace->glyph->advance.x >> 6) + drawXAdvanceOffset;

			glyphIndexPrevious = glyphIndex;
		}

		// Creating a texture from the buffer
		m_Texture = new Texture();
		m_Texture->Load(imageBuffer, true);
	}

	void Font::Clean() {
		m_Texture->Clean();
		delete m_Texture;
	}
}