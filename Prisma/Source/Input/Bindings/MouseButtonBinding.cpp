#include "MouseButtonBinding.h"

namespace Prisma::Input {
	void MouseButtonBinding::Update(const Window &window) {
		m_DownPrevious = m_Down;
		m_Down = glfwGetMouseButton(window.GetGLFWWindow(), m_GLFWMouseButton) == GLFW_PRESS;
	}
}