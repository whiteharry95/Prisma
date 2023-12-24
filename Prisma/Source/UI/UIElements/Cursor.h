#pragma once

#include "UIElement.h"
#include "../../Graphics/Textures/Texture.h"

namespace Prisma::UI::UIElements {
	class Cursor : public UIElement {
		const Graphics::Texture *m_Texture;

	public:
		void Load(const Graphics::GraphicsLoadingBatch &graphicsLoadingBatch) override;
		void Render(Graphics::Renderer &renderer) override;
	};
}