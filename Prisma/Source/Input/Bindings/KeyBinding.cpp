#include "KeyBinding.h"

#include "../../Application.h"

namespace Prisma::Input {
	void KeyBinding::Update() {
		m_DownPrevious = m_Down;
		m_Down = glfwGetKey(Application::Get().GetWindow().GetGLFWWindow(), m_GLFWKey) == GLFW_PRESS;
	}
}