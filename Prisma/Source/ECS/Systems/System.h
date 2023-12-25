#pragma once

#include "../ECSPackages.h"

namespace Prisma::ECS {
	class ECSManager;

	class System {
	public:
		virtual void Update(ECSManager &ecsManager, ECSUpdatePackage &package) = 0;
		virtual void Render(ECSManager &ecsManager, ECSRenderPackage &package) = 0;
	};
}