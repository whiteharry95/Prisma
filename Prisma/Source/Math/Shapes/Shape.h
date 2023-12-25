#pragma once

#include <glm/glm.hpp>

namespace Prisma::Math::Shapes {
	class Shape {
	public:
		virtual bool DoesContain(glm::vec2 position) = 0;
	};
}