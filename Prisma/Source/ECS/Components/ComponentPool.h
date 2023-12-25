#pragma once

#include <vector>
#include <unordered_map>
#include <utility>

#include "../Entity.h"

namespace Prisma::ECS {
	class ComponentPoolBase {
	};

	template<typename T>
	class ComponentPool : public ComponentPoolBase {
		std::vector<T> m_Components;
		std::unordered_map<Entity, unsigned int> m_EntityToComponentIndex;

	public:
		T &GetComponentOfEntity(Entity entity);
		void AddComponent(Entity entity);
	};

	template<typename T>
	inline T &ComponentPool<T>::GetComponentOfEntity(Entity entity) {
		return m_Components[m_EntityToComponentIndex[entity]];
	}

	template<typename T>
	inline void ComponentPool<T>::AddComponent(Entity entity) {
		m_EntityToComponentIndex[entity] = m_Components.size();
		m_Components.emplace_back();
	}
}