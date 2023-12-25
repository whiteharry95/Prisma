#include "SpriteRenderingSystem.h"

#include "../../Input/InputManager.h"
#include "../ECSManager.h"
#include "../Components/Transform.h"
#include "../../Graphics/Rendering/Renderer.h"

namespace Prisma::ECS {
	void SpriteRenderingSystem::Update(ECSManager &ecsManager, ECSUpdatePackage &package) {
		auto transformPool = ecsManager.GetComponentPool<Components::Transform>();

		if (package.InputManager.GetKeyBinding(Input::KeyBinding::MoveRight).IsDown()) {
			transformPool->GetComponentOfEntity(0).Position.x++;
		}
	}

	void SpriteRenderingSystem::Render(ECSManager &ecsManager, ECSRenderPackage &package) {
		auto transformPool = ecsManager.GetComponentPool<Components::Transform>();

		const Graphics::Texture &texture = package.TextureManager.GetTexture(package.TextureManager.GetTextureID("Player"));
		package.Renderer.SubmitTexture(0, Graphics::RenderLayer::ID::Player, { }, { transformPool->GetComponentOfEntity(0).Position, glm::vec2(32.f) }, 0.f, { }, 1.f);
	}
}