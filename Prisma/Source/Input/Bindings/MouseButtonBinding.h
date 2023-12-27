#pragma once

namespace Prisma::Input {
	typedef int GLFWMouseButton;

	class MouseButtonBinding {
		GLFWMouseButton m_GLFWMouseButton = 0;

		bool m_Down = false;
		bool m_DownPrevious = false;

	public:
		enum ID : unsigned char {
			Shoot,
			COUNT
		};

		void Update();

		GLFWMouseButton GetGLFWMouseButton() const {
			return m_GLFWMouseButton;
		}

		void SetGLFWMouseButton(GLFWMouseButton glfwMouseButton) {
			m_GLFWMouseButton = glfwMouseButton;
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