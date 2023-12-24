#include "Renderer.h"
#include "../../Application.h"

#include <iostream>
#include <glad/glad.h>

namespace Prisma::Graphics {
	void Renderer::Init(const TextureManager *textureManager, const FontManager *fontManager, const ShaderManager *shaderManager) {
		m_TextureManager = textureManager;
		m_FontManager = fontManager;
		m_ShaderManager = shaderManager;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, (int *)(&RenderBatch::MaxUniqueTextureGLIDCount));
		RenderBatch::MaxUniqueTextureGLIDCount = std::min(32, static_cast<int>(RenderBatch::MaxUniqueTextureGLIDCount));

		for (RenderLayer &layer : m_Layers) {
			layer.Init(800, textureManager, fontManager, shaderManager);
		}
	}

	void Renderer::Update() {
		for (RenderLayer &layer : m_Layers) {
			layer.Update();
		}
	}

	void Renderer::Render(const Window &window) {
		for (RenderLayer &layer : m_Layers) {
			layer.Render(window);
		}
	}

	void Renderer::Clean() {
		for (RenderLayer &layer : m_Layers) {
			layer.Clean();
		}
	}

	void Renderer::Clear() {
		glClearColor(0, 0, 0, 255);
		glClear(GL_COLOR_BUFFER_BIT);

		for (RenderLayer &layer : m_Layers) {
			layer.Clear();
		}
	}

	void Renderer::SubmitTexture(TextureID id, RenderLayer::LayerID layerID, SourceRectangle sourceRect, const Math::Shapes::Rectangle &destinationRect, float rotation, glm::vec2 origin, float opacity) {
		m_Layers[layerID].Submit(m_TextureManager->GetTexture(id), sourceRect, destinationRect, rotation, origin, opacity);
	}

	void Renderer::SubmitFont(FontID id, const std::string &text, glm::vec2 position, Font::HorizontalAlignment horizontalAlignment, Font::VerticalAlignment verticalAlignment) {
		const Font &font = m_FontManager->GetFont(id);

		FT_Face ftFace = m_FontManager->GetFontFace(font.GetFaceID()).GetFTFace();
		FT_Set_Char_Size(ftFace, font.GetPointSize() << 6, 0, FontFace::DPI, 0);

		/* ----- Setting Draw Positions ----- */
		glm::vec2 drawPosition = { }; // The draw position of the current glyph (cumulative)
		std::vector<glm::vec2> drawPositions; // The positions on the screen where each glyph will be drawn
		unsigned short drawPositionIndex = 0;

		std::vector<float> lineWidths; // The total width of each line in the text

		unsigned int glyphIndexPrevious;

		for (int i = 0; i < text.length(); i++) {
			// Moving to a new line
			if (text[i] == '\n') {
				lineWidths.push_back(drawPosition.x);

				drawPosition.x = 0.f;
				drawPosition.y += ftFace->size->metrics.height >> 6;

				continue;
			}

			// Loading the glyph
			unsigned int glyphIndex = FT_Get_Char_Index(ftFace, text[i]);

			FT_Load_Glyph(ftFace, glyphIndex, FT_LOAD_DEFAULT);
			FT_Render_Glyph(ftFace->glyph, FT_RENDER_MODE_NORMAL);

			// Applying kerning
			if (drawPositionIndex > 0) {
				FT_Vector kerning;
				FT_Get_Kerning(ftFace, glyphIndexPrevious, glyphIndex, FT_KERNING_DEFAULT, &kerning);

				drawPosition.x += kerning.x >> 6;
			}

			// Adding the draw position of this glyph to the vector
			drawPositions.push_back({ drawPosition.x + ftFace->glyph->bitmap_left, drawPosition.y - ftFace->glyph->bitmap_top + (ftFace->size->metrics.ascender >> 6) });
			drawPosition.x += ftFace->glyph->advance.x >> 6;

			drawPositionIndex++;

			glyphIndexPrevious = glyphIndex;
		}

		lineWidths.push_back(drawPosition.x);

		float height = drawPosition.y + (ftFace->size->metrics.height >> 6); // The total height of the text

		/* -----Drawing the Glyphs ----- */
		unsigned char lineIndex = 0; // The index of the line being drawn

		drawPositionIndex = 0;

		for (int i = 0; i < text.length(); i++) {
			if (text[i] == '\n') {
				lineIndex++;
				continue;
			}

			SourceRectangle sourceRect = font.GetSourceRectOfCharacter(text[i]);

			Math::Shapes::Rectangle destinationRect;

			destinationRect.SetPosition({ position.x + drawPositions[drawPositionIndex].x - ((lineWidths[lineIndex] * static_cast<float>(horizontalAlignment)) / 2.f), position.y + drawPositions[drawPositionIndex].y - ((height * static_cast<float>(verticalAlignment)) / 2.f) });
			destinationRect.SetSize({ sourceRect.Width, sourceRect.Height });

			m_Layers[RenderLayer::LayerID::UI].Submit(font.GetTexture(), sourceRect, destinationRect, 0.f, glm::vec2(), 1.f);

			drawPositionIndex++;
		}
	}
}