#pragma once

#include <array>
#include <glm/glm.hpp>

#include "Bindings/KeyBinding.h"
#include "Bindings/MouseButtonBinding.h"
#include "Bindings/GamepadButtonBinding.h"
#include "Bindings/GamepadAxisBinding.h"

namespace Prisma::Input {
	class InputManager {
		std::array<KeyBinding, KeyBinding::BindingID::Count> m_KeyBindings;
		std::array<MouseButtonBinding, MouseButtonBinding::BindingID::Count> m_MouseButtonBindings;
		std::array<GamepadButtonBinding, GamepadButtonBinding::BindingID::Count> m_GamepadButtonBindings;
		std::array<GamepadAxisBinding, GamepadAxisBinding::BindingID::Count> m_GamepadAxisBindings;

		glm::dvec2 m_MousePosition;

		char m_GamepadJoystickIndex = -1;

		InputManager(const InputManager &) = delete;

	public:
		InputManager() = default;

		void Init();
		void Update();

		const KeyBinding &GetKeyBinding(KeyBinding::BindingID id) const {
			return m_KeyBindings[id];
		}

		const MouseButtonBinding &GetMouseButtonBinding(MouseButtonBinding::BindingID id) const {
			return m_MouseButtonBindings[id];
		}

		const GamepadButtonBinding &GetGamepadButtonBinding(GamepadButtonBinding::BindingID id) const {
			return m_GamepadButtonBindings[id];
		}

		const GamepadAxisBinding &GetGamepadAxisBinding(GamepadAxisBinding::BindingID id) const {
			return m_GamepadAxisBindings[id];
		}

		glm::dvec2 GetMousePosition() const {
			return m_MousePosition;
		}

		char GetGamepadJoystickIndex() const {
			return m_GamepadJoystickIndex;
		}

		bool IsGamepadConnected() const {
			return m_GamepadJoystickIndex != -1;
		}
	};
}