#include "Rectangle.h"

#include "../../Debugging.h"

namespace Prisma::Math::Shapes {
	Rectangle::Rectangle(glm::vec2 position, glm::vec2 size) : m_Position(position) {
		SetSize(size);
	}

	bool Rectangle::DoesContain(glm::vec2 position) {
		return position.x >= m_Position.x && position.y >= m_Position.y && position.x < GetRight() && position.y < GetBottom();
	}

	void Rectangle::SetSize(glm::vec2 size) {
		if (size.x < 0.f || size.y < 0.f) {
			Debugging::Log("Neither the width nor height of a rectangle can be negative");
			return;
		}

		m_Size = size;
	}
}