#include "Transform.h"

namespace Prisma::ECS::Components {
	Transform::Transform(glm::vec2 position, float rotation, glm::vec2 scale) : Position(position), Rotation(rotation), Scale(scale) {
	}
}