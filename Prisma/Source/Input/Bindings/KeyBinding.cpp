#include "KeyBinding.h"

#include "../../Game.h"

namespace Prisma::Input {
	void KeyBinding::Update() {
		m_DownPrevious = m_Down;
		m_Down = glfwGetKey(Game::Get().GetWindow().GetGLFWWindow(), m_GLFWKey) == GLFW_PRESS;
	}
}