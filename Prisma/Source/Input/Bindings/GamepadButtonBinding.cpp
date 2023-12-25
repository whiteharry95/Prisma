#include "GamepadButtonBinding.h"

#include <GLFW/glfw3.h>

#include "../InputManager.h"

namespace Prisma::Input {
	void GamepadButtonBinding::Update(const InputManager &inputManager) {
		m_DownPrevious = m_Down;

		m_Down = false;
		GLFWgamepadstate gamepadState;

		if (inputManager.IsGamepadConnected()) {
			if (glfwGetGamepadState(inputManager.GetGamepadJoystickIndex(), &gamepadState)) {
				if (gamepadState.buttons[m_GLFWGamepadButton] == GLFW_PRESS) {
					m_Down = true;
				}
			} else {
				m_DownPrevious = false;
			}
		} else {
			m_DownPrevious = false;
		}
	}
}