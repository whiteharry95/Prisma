#pragma once

#include "../../Graphics/GraphicsLoadingBatch.h"
#include "../../Graphics/Rendering/Renderer.h"

namespace Prisma::UI::UIElements {
	class UIElement {
	public:
		virtual void Load(const Graphics::GraphicsLoadingBatch &graphicsLoadingBatch) {
		}

		virtual void Update() {
		}

		virtual void Render(Graphics::Renderer &renderer) {
		}
	};
}