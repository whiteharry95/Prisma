#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <AL/al.h>
#include <AL/alc.h>

#include "Window.h"

#include "Input/InputManager.h"

#include "Graphics/Textures/TextureManager.h"
#include "Graphics/Fonts/FontManager.h"
#include "Graphics/Shaders/ShaderManager.h"

#include "Graphics/Rendering/Renderer.h"

#include "Audio/Sounds/SoundManager.h"
#include "Audio/Music/MusicManager.h"

namespace Prisma {
	class Application {
		FT_Library m_FTLibrary = NULL;

		ALCdevice *m_ALDevice = nullptr;
		ALCcontext *m_ALContext = nullptr;

		Window *m_Window = nullptr;

		Input::InputManager m_InputManager;

		Graphics::TextureManager m_TextureManager;
		Graphics::FontManager m_FontManager;
		Graphics::ShaderManager m_ShaderManager;

		Graphics::Renderer m_Renderer;

		Audio::SoundManager m_SoundManager;
		Audio::MusicManager m_MusicManager;

		Application() = default;
		Application(const Application &) = delete;

	public:
		static Application &Get() {
			static Application app;
			return app;
		}

		void Run();

		FT_Library GetFTLibrary() const {
			return m_FTLibrary;
		}

		Window &GetWindow() const {
			return *m_Window;
		}
	};
}