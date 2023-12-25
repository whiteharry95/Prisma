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
#include "ECS/ECSManager.h"

#include "Camera.h"

#include "UI/UIManager.h"

namespace Prisma {
	class Game {
		FT_Library m_FTLibrary;

		Window *m_Window;

		Input::InputManager m_InputManager;

		Graphics::TextureManager m_TextureManager;
		Graphics::FontManager m_FontManager;
		Graphics::ShaderManager m_ShaderManager;

		Graphics::Renderer m_Renderer;

		Audio::AudioManager m_AudioManager;
		ECS::ECSManager m_ECSManager;

		Camera m_Camera;

		UI::UIManager m_UIManager;

		Game() = default;
		Game(const Game &) = delete;

	public:
		static Game &Get() {
			static Game game;
			return game;
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