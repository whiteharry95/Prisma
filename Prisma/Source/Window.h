#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Prisma {
	class Window {
		GLFWwindow *m_GLFWWindow;

		Window(GLFWwindow *glfwWindow);
		Window(const Window &) = delete;

	public:
		/// <returns>A pointer to a newly created window, or nullptr if an error occurred</returns>
		static Window *Create(const std::string &title, int width, int height);

		~Window();

		GLFWwindow *GetGLFWWindow() const {
			return m_GLFWWindow;
		}

		glm::ivec2 GetSize() const;
	};
}