#pragma once

#include <array>
#include <glm/glm.hpp>

#include "../Fonts/Font.h"
#include "RenderLayer.h"
#include "../SourceRectangle.h"
#include "../../Math/Shapes/Rectangle.h"
#include "../Textures/Texture.h"
#include "../../Window.h"

namespace Prisma::Graphics {
	class Renderer {
		std::array<RenderLayer, static_cast<size_t>(RenderLayer::ID::COUNT)> m_Layers;

		const TextureManager *m_TextureManager;
		const FontManager *m_FontManager;
		const ShaderManager *m_ShaderManager;

	public:
		void Init(const TextureManager *textureManager, const FontManager *fontManager, const ShaderManager *shaderManager);
		void Update();
		void Render(const Window &window);
		void Clean();
		void Clear();

		/// <summary>
		/// Submits texture rendering information to a render batch within the given render layer
		/// </summary>
		void SubmitTexture(TextureID id, RenderLayer::ID layerID, SourceRectangle sourceRect, const Math::Shapes::Rectangle &destinationRect, float rotation, glm::vec2 origin, float opacity);

		/// <summary>
		/// Submits multiple sets of texture rendering information to the given render layer to ultimately draw a piece of text with the given font
		/// </summary>
		void SubmitFont(FontID id, const std::string &text, glm::vec2 position, Font::HorizontalAlignment horizontalAlignment, Font::VerticalAlignment verticalAlignment);
	};
}