#pragma once

namespace Prisma {
	namespace Input {
		class InputManager;
	}

	namespace Graphics {
		class Renderer;
		class TextureManager;
	}

	class Camera;

	namespace ECS {
		struct ECSUpdatePackage {
			const Input::InputManager &InputManager;
			const Camera &Camera;
		};

		struct ECSRenderPackage {
			Graphics::Renderer &Renderer;
			const Graphics::TextureManager &TextureManager;
			const Camera &Camera;
		};
	}
}