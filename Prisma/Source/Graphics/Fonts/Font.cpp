#include "Font.h"

#include <glad/glad.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "../../Application.h"
#include "FontFace.h"
#include "../Textures/RGBAImageBuffer.h"

namespace Prisma::Graphics {
	Font::Font(FontID id, const FontFace &face, unsigned short pointSize) : m_ID(id), m_FaceID(face.GetID()), m_PointSize(pointSize) {
		if (pointSize < 8) {
			Debugging::LogWarning("Loading a font with a point size below 8");
		}

		// Preparing the font face
		FT_Face ftFace = face.GetFTFace();
		FT_Set_Char_Size(ftFace, pointSize << 6, 0, FontFace::DPI, 0);

		// Creating and clearing an image buffer
		unsigned short height = static_cast<unsigned short>((ftFace->size->metrics.height * 8) >> 6);
		unsigned short width = (height * 5) / 3;

		RGBAImageBuffer imageBuffer(width, height);
		imageBuffer.ClearPixels({ 255, 255, 255, 0 });

		// Adding glyphs to the texture
		short drawX = 0;
		short drawY = 0;

		short drawXAdvanceOffset = 5; // An offset to help ensure the glyphs don't overlap

		unsigned int glyphIndexPrevious;

		for (char c = CharacterRangeStart; c <= CharacterRangeEnd; c++) {
			unsigned int glyphIndex = FT_Get_Char_Index(ftFace, c);

			FT_Load_Glyph(ftFace, glyphIndex, FT_LOAD_DEFAULT);
			FT_Render_Glyph(ftFace->glyph, FT_RENDER_MODE_NORMAL);

			short drawXOffset = ftFace->glyph->bitmap_left;
			short drawYOffset = static_cast<short>((ftFace->size->metrics.ascender >> 6) - ftFace->glyph->bitmap_top);

			short drawXShift = 0;

			if (drawXOffset < 0) {
				drawXShift = -drawXOffset;
			}

			if (drawX + drawXShift + (ftFace->glyph->advance.x >> 6) + drawXAdvanceOffset >= width) {
				drawX = 0;
				drawY += static_cast<short>(ftFace->size->metrics.height >> 6);
			}

			drawX += drawXShift;

			SourceRectangle characterSourceRect = {
				static_cast<unsigned short>(drawX + drawXOffset), static_cast<unsigned short>(drawY + drawYOffset),
				static_cast<unsigned short>(ftFace->glyph->bitmap.width), static_cast<unsigned short>(ftFace->glyph->bitmap.rows + 1)
			};

			m_CharacterSourceRects[c - CharacterRangeStart] = characterSourceRect;

			for (unsigned int y = 0; y < ftFace->glyph->bitmap.rows; y++) {
				for (unsigned int x = 0; x < ftFace->glyph->bitmap.width; x++) {
					unsigned char alpha = ftFace->glyph->bitmap.buffer[(y * ftFace->glyph->bitmap.width) + x];

					if (alpha > 0) {
						imageBuffer.SetPixel(drawX + drawXOffset + x, drawY + drawYOffset + y, { 255, 255, 255, alpha });
					}
				}
			}

			drawX += static_cast<short>((ftFace->glyph->advance.x >> 6)) + drawXAdvanceOffset;

			glyphIndexPrevious = glyphIndex;
		}

		// Creating a texture from the buffer
		m_Texture = new Texture(imageBuffer, true);
	}

	void Font::Clean() {
		m_Texture->Clean();
		delete m_Texture;
	}
}