#include "GamepadAxisBinding.h"

#include <GLFW/glfw3.h>

#include "../InputManager.h"

namespace Prisma::Input {
	void GamepadAxisBinding::Update(const InputManager &inputManager) {
		GLFWgamepadstate gamepadState;

		if (inputManager.IsGamepadConnected()) {
			if (glfwGetGamepadState(inputManager.GetGamepadJoystickIndex(), &gamepadState)) {
				m_AxisValue = gamepadState.axes[m_GLFWGamepadAxis];

				if (std::abs(m_AxisValue) <= m_AxisDeadzone) {
					m_AxisValue = 0.f;
				}
			}
		}
	}
}