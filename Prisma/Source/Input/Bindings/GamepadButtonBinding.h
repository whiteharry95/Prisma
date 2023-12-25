#pragma once

namespace Prisma::Input {
	typedef int GLFWGamepadButton;

	class InputManager;

	class GamepadButtonBinding {
		GLFWGamepadButton m_GLFWGamepadButton;

		bool m_Down;
		bool m_DownPrevious;

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