#pragma once

#include <unordered_map>
#include <typeindex>
#include <utility>

#include "Components/ComponentPool.h"
#include "Components/Transform.h"

namespace Prisma::ECS {
	class ECSManager {
		std::unordered_map<std::type_index, ComponentPoolBase *> m_ComponentPools;

	public:
		void Init();
		void Update();
		void Render();
		void Clean();

		template<typename T> void AddComponentPool();

		template<typename T> T &GetComponentOfEntity(Entity entity);
		template<typename T> void AddComponentToEntity(Entity entity);
	};

	template<typename T>
	inline void ECSManager::AddComponentPool() {
		m_ComponentPools[typeid(T)] = new ComponentPool<T>();
	}

	template<typename T>
	T &ECSManager::GetComponentOfEntity(Entity entity) {
		return static_cast<ComponentPool<T> *>(m_ComponentPools[typeid(T)])->GetComponentOfEntity(entity);
	}

	template<typename T>
	void ECSManager::AddComponentToEntity(Entity entity) {
		static_cast<ComponentPool<T> *>(m_ComponentPools[typeid(T)])->AddComponent(entity);
	}
}