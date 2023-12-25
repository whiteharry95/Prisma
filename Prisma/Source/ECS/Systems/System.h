#pragma once

namespace Prisma::ECS::Systems {
	class System {
	public:
		System() {
		}

		virtual void Update() = 0;
		virtual void Render() = 0;
	};
}