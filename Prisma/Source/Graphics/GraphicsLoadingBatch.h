#pragma once

#include "../Graphics/Textures/TextureManager.h"
#include "../Graphics/Fonts/FontManager.h"
#include "../Graphics/Shaders/ShaderManager.h"

namespace Prisma::Graphics {
	struct GraphicsLoadingBatch {
		const TextureManager &TextureManager;
		const FontManager &FontManager;
		const ShaderManager &ShaderManager;
	};
}