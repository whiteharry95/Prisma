#pragma once

namespace Prisma::Input {
	typedef int GLFWGamepadAxis;

	class InputManager;

	class GamepadAxisBinding {
		GLFWGamepadAxis m_GLFWGamepadAxis = 0;

		float m_AxisValue = 0.f;
		float m_AxisDeadzone = 0.1f;

	public:
		enum ID : unsigned char {
			MoveHorizontally,
			MoveVertically,

			COUNT
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