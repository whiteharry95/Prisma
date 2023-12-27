#pragma once

namespace Prisma::Input {
	typedef int GLFWGamepadButton;

	class InputManager;

	class GamepadButtonBinding {
		GLFWGamepadButton m_GLFWGamepadButton = 0;

		bool m_Down = false;
		bool m_DownPrevious = false;

	public:
		enum ID : unsigned char {
			Shoot,
			COUNT
		};

		void Update(const InputManager &inputManager);

		GLFWGamepadButton GetGLFWGamepadButton() const {
			return m_GLFWGamepadButton;
		}

		void SetGLFWGamepadButton(GLFWGamepadButton glfwGamepadButton) {
			m_GLFWGamepadButton = glfwGamepadButton;
		}

		bool IsDown() const {
			return m_Down;
		}

		bool IsPressed() const {
			return m_Down && !m_DownPrevious;
		}

		bool IsReleased() const {
			return !m_Down && m_DownPrevious;
		}
	};
}