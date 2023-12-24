#pragma once

#include <glm/glm.hpp>

#include "Shape.h"

namespace Prisma::Math::Shapes {
	class Rectangle : public Shape {
		glm::vec2 m_Position;
		glm::vec2 m_Size;

	public:
		Rectangle() = default;
		Rectangle(glm::vec2 position, glm::vec2 size);

		glm::vec2 GetPosition() const {
			return m_Position;
		}

		void SetPosition(glm::vec2 position) {
			m_Position = position;
		}

		glm::vec2 GetSize() const {
			return m_Size;
		}

		void SetSize(glm::vec2 size);

		float GetRight() const {
			return m_Position.x + m_Size.x;
		}

		float GetBottom() const {
			return m_Position.y + m_Size.y;
		}
	};
}