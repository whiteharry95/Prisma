#pragma once

#include <glm/glm.hpp>

namespace Prisma {
	class Camera {
		glm::vec2 m_Position;

	public:
		void Init();
		void Update();
	};
}