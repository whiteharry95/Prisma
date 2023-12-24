#include "InputManager.h"

namespace Prisma::Input {
	InputManager::InputManager(const Window &window) : m_Window(window) {
	}

	void InputManager::Init() {
		m_KeyBindings[KeyBinding::BindingID::MoveRight].SetGLFWKey(GLFW_KEY_D);
		m_KeyBindings[KeyBinding::BindingID::MoveLeft].SetGLFWKey(GLFW_KEY_A);
		m_KeyBindings[KeyBinding::BindingID::MoveDown].SetGLFWKey(GLFW_KEY_S);
		m_KeyBindings[KeyBinding::BindingID::MoveUp].SetGLFWKey(GLFW_KEY_W);

		m_MouseButtonBindings[MouseButtonBinding::BindingID::Shoot].SetGLFWMouseButton(GLFW_MOUSE_BUTTON_LEFT);

		m_GamepadButtonBindings[GamepadButtonBinding::BindingID::Shoot].SetGLFWGamepadButton(GLFW_GAMEPAD_BUTTON_X);

		m_GamepadAxisBindings[GamepadAxisBinding::BindingID::MoveHorizontally].SetGLFWGamepadAxis(GLFW_GAMEPAD_AXIS_LEFT_X);
		m_GamepadAxisBindings[GamepadAxisBinding::BindingID::MoveVertically].SetGLFWGamepadAxis(GLFW_GAMEPAD_AXIS_LEFT_Y);
	}

	void InputManager::Update() {
		// Keyboard input
		for (KeyBinding &keyBinding : m_KeyBindings) {
			keyBinding.Update(m_Window);
		}

		// Mouse input
		glfwGetCursorPos(m_Window.GetGLFWWindow(), &m_MousePosition.x, &m_MousePosition.y);

		for (MouseButtonBinding &mouseButtonBinding : m_MouseButtonBindings) {
			mouseButtonBinding.Update(m_Window);
		}

		// Gamepad input
		m_GamepadJoystickIndex = -1;

		for (int i = 0; i <= GLFW_JOYSTICK_LAST; i++) {
			GLFWgamepadstate gamepadState;

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