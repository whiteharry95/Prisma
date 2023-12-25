#pragma once

#include "System.h"

namespace Prisma::ECS {
	class SpriteRenderingSystem : public System {
	public:
		void Update(ECSManager &ecsManager, ECSUpdatePackage &package) override;
		void Render(ECSManager &ecsManager, ECSRenderPackage &package) override;
	};
}