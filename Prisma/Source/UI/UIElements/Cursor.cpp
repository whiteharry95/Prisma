#include "Cursor.h"

namespace Prisma::UI::UIElements {
	void Cursor::Load(const Graphics::GraphicsLoadingBatch &graphicsLoadingBatch) {
		//m_Texture = graphicsLoadingBatch.TextureManager.GetTexture("UI/Cursor");
	}

	void Cursor::Render(Graphics::Renderer &renderer) {
		//renderer.SubmitTexture(m_Texture, Graphics::RenderLayerID::UI, { }, { glm::vec2(), glm::vec2(32.f) }, 0.f, { }, 1.f);
	}
}