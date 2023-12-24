#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Window.h"

#include "Graphics/Textures/TextureManager.h"
#include "Graphics/Fonts/FontManager.h"
#include "Graphics/Shaders/ShaderManager.h"

#include "Graphics/Rendering/Renderer.h"

#include "UI/UIManager.h"

namespace Prisma {
	class Application {
		FT_Library m_FTLibrary;

		Window *m_Window;

		Graphics::TextureManager m_TextureManager;
		Graphics::FontManager m_FontManager;
		Graphics::ShaderManager m_ShaderManager;

		Graphics::Renderer m_Renderer;

		UI::UIManager m_UIManager;

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
	};
}