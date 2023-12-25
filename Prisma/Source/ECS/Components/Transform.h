#pragma once

#include <glm/glm.hpp>

namespace Prisma::ECS::Components {
	struct Transform {
		glm::vec2 Position;
		float Rotation;
		glm::vec2 Scale;

		Transform(glm::vec2 position = { }, float rotation = 0.f, glm::vec2 scale = glm::vec2(1.f));
	};
}