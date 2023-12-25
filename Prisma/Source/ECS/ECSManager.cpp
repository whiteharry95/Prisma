#include "ECSManager.h"

#include "Components/Transform.h"
#include "Systems/SpriteRenderingSystem.h"

namespace Prisma::ECS {
	void ECSManager::Init() {
		AddComponentPool<Components::Transform>();
		AddSystem<SpriteRenderingSystem>();

		GetComponentPool<Components::Transform>()->AddComponent(0);
	}

	void ECSManager::Update(ECSUpdatePackage &&package) {
		for (System *system : m_Systems) {
			system->Update(*this, package);
		}
	}

	void ECSManager::Render(ECSRenderPackage &&package) {
		for (System *system : m_Systems) {
			system->Render(*this, package);
		}
	}

	void ECSManager::Clean() {
		for (auto &componentPool : m_ComponentPools) {
			delete componentPool.second;
		}
	}
}