#include "KeyBinding.h"

namespace Prisma::Input {
	void KeyBinding::Update(const Window &window) {
		m_DownPrevious = m_Down;
		m_Down = glfwGetKey(window.GetGLFWWindow(), m_GLFWKey) == GLFW_PRESS;
	}
}