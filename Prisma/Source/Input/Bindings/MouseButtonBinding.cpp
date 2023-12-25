#include "MouseButtonBinding.h"

#include "../../Game.h"

namespace Prisma::Input {
	void MouseButtonBinding::Update() {
		m_DownPrevious = m_Down;
		m_Down = glfwGetMouseButton(Game::Get().GetWindow().GetGLFWWindow(), m_GLFWMouseButton) == GLFW_PRESS;
	}
}