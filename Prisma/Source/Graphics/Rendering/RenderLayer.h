#pragma once

#include <vector>

#include "RenderBatch.h"
#include "../Textures/Texture.h"
#include "../../Math/Shapes/Rectangle.h"
#include "../SourceRectangle.h"
#include "../../Window.h"
#include "../Textures/TextureManager.h"
#include "../Fonts/FontManager.h"
#include "../Shaders/ShaderManager.h"

namespace Prisma::Graphics {
	class RenderLayer {
		static const unsigned char VertexBufferElementCountPerRender = 44;
		static const unsigned char ElementBufferElementCountPerRender = 6;

		std::vector<RenderBatch *> m_RenderBatches;
		unsigned short m_RenderBatchCount;

		unsigned short m_LastRenderBatchPopTime; // How many updates since the last render batch in the vector was used
		const unsigned short m_LastRenderBatchPopTimeMax = 1200;

		unsigned short m_MaxRenderCountPerBatch;

		unsigned short m_UniqueTextureIDCount;

		ShaderProgramID m_TextureShaderProgramID;

		const TextureManager *m_TextureManager = nullptr;
		const FontManager *m_FontManager = nullptr;
		const ShaderManager *m_ShaderManager = nullptr;

		RenderLayer(const RenderLayer &) = delete;

	public:
		enum ID : unsigned char {
			Player,
			Projectiles,
			UI,

			COUNT
		};

		RenderLayer() = default;

		void Init(unsigned short maxRenderCountPerBatch, const TextureManager *m_TextureManager, const FontManager *m_FontManager, const ShaderManager *m_ShaderManager);
		void Update();
		void Render(const Window &window);
		void Clean();

		void Clear();

		void Submit(const Texture &texture, SourceRectangle sourceRect, const Math::Shapes::Rectangle &destinationRect, float rotation, glm::vec2 origin, float opacity);
	};
}