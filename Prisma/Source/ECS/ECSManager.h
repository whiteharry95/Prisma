#pragma once

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <utility>

#include "Systems/System.h"
#include "Components/ComponentPool.h"
#include "ECSPackages.h"

namespace Prisma::ECS {
	class ECSManager {
		std::vector<System *> m_Systems;
		std::unordered_map<std::type_index, ComponentPoolBase *> m_ComponentPools;

		template<typename T> void AddSystem();
		template<typename T> void AddComponentPool();

	public:
		void Init();
		void Update(ECSUpdatePackage &&package);
		void Render(ECSRenderPackage &&package);
		void Clean();

		template<typename T> ComponentPool<T> *GetComponentPool();

		template<typename T> T &GetComponentOfEntity(Entity entity);
		template<typename T> void AddComponentToEntity(Entity entity);
	};

	template<typename T>
	inline void ECSManager::AddSystem() {
		m_Systems.push_back(new T());
	}

	template<typename T>
	inline void ECSManager::AddComponentPool() {
		m_ComponentPools[typeid(T)] = new ComponentPool<T>();
	}

	template<typename T>
	inline ComponentPool<T> *ECSManager::GetComponentPool() {
		return static_cast<ComponentPool<T> *>(m_ComponentPools[typeid(T)]);
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