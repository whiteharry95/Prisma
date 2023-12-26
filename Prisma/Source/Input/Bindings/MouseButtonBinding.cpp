#include "MouseButtonBinding.h"

#include "../../Application.h"

namespace Prisma::Input {
	void MouseButtonBinding::Update() {
		m_DownPrevious = m_Down;
		m_Down = glfwGetMouseButton(Application::Get().GetWindow().GetGLFWWindow(), m_GLFWMouseButton) == GLFW_PRESS;
	}
}