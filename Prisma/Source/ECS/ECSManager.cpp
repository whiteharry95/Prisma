#include "ECSManager.h"

namespace Prisma::ECS {
	void ECSManager::Init() {
		AddComponentPool<Components::Transform>();
	}

	void ECSManager::Update() {
	}

	void ECSManager::Render() {
	}

	void ECSManager::Clean() {
		for (auto &componentPool : m_ComponentPools) {
			delete componentPool.second;
		}
	}
}