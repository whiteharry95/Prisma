#include "Application.h"

#include "Debugging.h"

namespace Prisma {
	void Application::Run() {
		/* ----- Initialisation ----- */
		// Initialising GLFW
		glfwSetErrorCallback([](int error, const char *description) {
			Debugging::LogError(description, "GLFW"); // Logs a provided error message whenever a GLFW error occurs
		});

		glfwInit();

		// Initialising FreeType
		if (FT_Init_FreeType(&m_FTLibrary)) {
			Debugging::LogError("Failed to initialise FreeType");
		}

		// Opening a playback device for OpenAL
		m_ALDevice = alcOpenDevice(nullptr);

		if (!m_ALDevice) {
			Debugging::LogError("Failed to open a playback device for OpenAL");
		}

		// Creating an OpenAL context
		m_ALContext = alcCreateContext(m_ALDevice, nullptr);

		if (!m_ALContext) {
			Debugging::LogError("Failed to create an OpenAL context");
		}

		alcMakeContextCurrent(m_ALContext);

		// Creating the window
		m_Window = Window::Create("Prisma", 1280, 720);

		// Initialising Glad
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			Debugging::LogError("Failed to initialise Glad");
		}

		// Initialising various managers
		m_InputManager.Init();

		m_TextureManager.Init();
		m_FontManager.Init();
		m_ShaderManager.Init();

		m_Renderer.Init(&m_TextureManager, &m_FontManager, &m_ShaderManager);

		m_SoundManager.Init();
		m_MusicManager.Init();

		/* ----- Main Loop ----- */
		double frameTimePrevious = 0.;
		bool frameTimePreviousSet = false;

		const double targetFPS = 60.;

		const double targetFrameDuration = 1. / targetFPS;
		double frameDurationAccumulated = 0.;

		while (!glfwWindowShouldClose(m_Window->GetGLFWWindow())) {
			/* --- Handling Frame Time --- */
			double frameTime = glfwGetTime();

			if (!frameTimePreviousSet) {
				frameTimePrevious = frameTime; // Ensures that the initial frame duration is 0
				frameTimePreviousSet = true;
			}

			double frameDuration = frameTime - frameTimePrevious;

			// Ignoring abnormally long frames
			if (frameDuration > targetFrameDuration * 8.) {
				frameDuration = targetFrameDuration;
			}

			frameDurationAccumulated += frameDuration;

			// Ensuring that the game doesn't freeze if it can't update at 60hz
			if (frameDurationAccumulated > targetFrameDuration * 8.) {
				frameDurationAccumulated = 0.;
				frameDuration = targetFrameDuration;
			}

			frameTimePrevious = frameTime;

			/* --- Updating --- */
			while (frameDurationAccumulated >= targetFrameDuration) {
				m_InputManager.Update();
				m_Renderer.Update();
				m_SoundManager.Update();
				m_MusicManager.Update();

				frameDurationAccumulated -= targetFrameDuration;
			}

			/* --- Rendering --- */
			m_Renderer.Clear();
			m_Renderer.Render(*m_Window);

			glfwSwapBuffers(m_Window->GetGLFWWindow());

			/* --- Polling for Events --- */
			glfwPollEvents();
		}

		/* ----- Cleaning Up ----- */
		m_MusicManager.Clean();
		m_SoundManager.Clean();

		m_Renderer.Clean();

		m_ShaderManager.Clean();
		m_FontManager.Clean();
		m_TextureManager.Clean();

		delete m_Window;

		FT_Done_FreeType(m_FTLibrary);

		glfwTerminate();
	}
}