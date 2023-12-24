#include "Window.h"

#include "Debugging.h"

namespace Prisma {
	Window::Window(GLFWwindow *glfwWindow) : m_GLFWWindow(glfwWindow) {
	}

	Window *Window::Create(const std::string &title, int width, int height) {
		// Setting various window hints before creating the GLFW window
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow *glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

		// Return nullptr if the GLFW window couldn't be created
		if (glfwWindow == NULL) {
			return nullptr;
		}

		glfwMakeContextCurrent(glfwWindow);

		glfwSetFramebufferSizeCallback(glfwWindow, [](GLFWwindow *window, int width, int height) {
			glViewport(0, 0, width, height);
			Debugging::Log("Resized!");
		});

		glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); // Hides the cursor

		return new Window(glfwWindow);
	}

	Window::~Window() {
		glfwDestroyWindow(m_GLFWWindow);
	}

	glm::ivec2 Window::GetSize() const {
		int width, height;
		glfwGetWindowSize(m_GLFWWindow, &width, &height);

		return glm::ivec2(width, height);
	}
}