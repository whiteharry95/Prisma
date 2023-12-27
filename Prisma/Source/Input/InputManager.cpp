#include "InputManager.h"

#include "../Application.h"

namespace Prisma::Input {
	void InputManager::Init() {
		m_KeyBindings[KeyBinding::ID::MoveRight].SetGLFWKey(GLFW_KEY_D);
		m_KeyBindings[KeyBinding::ID::MoveLeft].SetGLFWKey(GLFW_KEY_A);
		m_KeyBindings[KeyBinding::ID::MoveDown].SetGLFWKey(GLFW_KEY_S);
		m_KeyBindings[KeyBinding::ID::MoveUp].SetGLFWKey(GLFW_KEY_W);

		m_MouseButtonBindings[MouseButtonBinding::ID::Shoot].SetGLFWMouseButton(GLFW_MOUSE_BUTTON_LEFT);

		m_GamepadButtonBindings[GamepadButtonBinding::ID::Shoot].SetGLFWGamepadButton(GLFW_GAMEPAD_BUTTON_X);

		m_GamepadAxisBindings[GamepadAxisBinding::ID::MoveHorizontally].SetGLFWGamepadAxis(GLFW_GAMEPAD_AXIS_LEFT_X);
		m_GamepadAxisBindings[GamepadAxisBinding::ID::MoveVertically].SetGLFWGamepadAxis(GLFW_GAMEPAD_AXIS_LEFT_Y);
	}

	void InputManager::Update() {
		/* ----- Keyboard Input ----- */
		for (KeyBinding &keyBinding : m_KeyBindings) {
			keyBinding.Update();
		}

		/* ----- Mouse Input ----- */
		glfwGetCursorPos(Application::Get().GetWindow().GetGLFWWindow(), &m_MousePosition.x, &m_MousePosition.y);

		for (MouseButtonBinding &mouseButtonBinding : m_MouseButtonBindings) {
			mouseButtonBinding.Update();
		}

		/* ----- Gamepad Input ----- */
		m_GamepadJoystickIndex = -1;

		for (int i = 0; i <= GLFW_JOYSTICK_LAST; i++) {
			if (glfwJoystickIsGamepad(i)) {
				m_GamepadJoystickIndex = i;
				break;
			}
		}

		for (GamepadButtonBinding &gamepadButtonBinding : m_GamepadButtonBindings) {
			gamepadButtonBinding.Update(*this);
		}

		for (GamepadAxisBinding &gamepadAxisBinding : m_GamepadAxisBindings) {
			gamepadAxisBinding.Update(*this);
		}
	}
}