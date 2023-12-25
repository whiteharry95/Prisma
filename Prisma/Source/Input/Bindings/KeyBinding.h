#pragma once

namespace Prisma::Input {
	typedef int GLFWKey;

	class KeyBinding {
		GLFWKey m_GLFWKey;

		bool m_Down;
		bool m_DownPrevious;

	public:
		enum ID : unsigned char {
			MoveRight,
			MoveLeft,
			MoveDown,
			MoveUp,

			COUNT
		};

		void Update();

		GLFWKey GetGLFWKey() const {
			return m_GLFWKey;
		}

		void SetGLFWKey(GLFWKey glfwKey) {
			m_GLFWKey = glfwKey;
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