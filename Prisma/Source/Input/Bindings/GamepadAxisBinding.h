#pragma once

namespace Prisma::Input {
	typedef int GLFWGamepadAxis;

	class InputManager;

	class GamepadAxisBinding {
		GLFWGamepadAxis m_GLFWGamepadAxis;

		float m_AxisValue;
		float m_AxisDeadzone = 0.1f;

	public:
		enum BindingID : unsigned char {
			MoveHorizontally,
			MoveVertically,

			Count
		};

		void Update(const InputManager &inputManager);

		GLFWGamepadAxis GetGLFWGamepadAxis() const {
			return m_GLFWGamepadAxis;
		}

		void SetGLFWGamepadAxis(GLFWGamepadAxis glfwGamepadAxis) {
			m_GLFWGamepadAxis = glfwGamepadAxis;
		}

		float GetAxisValue() const {
			return m_AxisValue;
		}

		float GetAxisDeadzone() const {
			return m_AxisDeadzone;
		}

		void SetAxisDeadzone(float deadzone) {
			m_AxisDeadzone = deadzone;
		}
	};
}