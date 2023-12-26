#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Window.h"

#include "Input/InputManager.h"

#include "Graphics/Textures/TextureManager.h"
#include "Graphics/Fonts/FontManager.h"
#include "Graphics/Shaders/ShaderManager.h"

#include "Graphics/Rendering/Renderer.h"

#include "Audio/AudioManager.h"

namespace Prisma {
	class Application {
		FT_Library m_FTLibrary;

		Window *m_Window;

		Input::InputManager m_InputManager;

		Graphics::TextureManager m_TextureManager;
		Graphics::FontManager m_FontManager;
		Graphics::ShaderManager m_ShaderManager;

		Graphics::Renderer m_Renderer;

		Audio::AudioManager m_AudioManager;

		Application() = default;
		Application(const Application &) = delete;

	public:
		static Application &Get() {
			static Application app;
			return app;
		}

		/// <returns>1 if an error occurs, otherwise 0</returns>
		int Run();

		FT_Library GetFTLibrary() const {
			return m_FTLibrary;
		}

		Window &GetWindow() const {
			return *m_Window;
		}
	};
}