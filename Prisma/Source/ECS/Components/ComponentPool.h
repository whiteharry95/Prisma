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
		std::unordered_map<EntityID, unsigned int> m_EntityIDToComponentIndex;

	public:
		T &GetComponentOfEntity(Entity entity);
		void AddComponent(Entity entity);
	};

	template<typename T>
	inline T &ComponentPool<T>::GetComponentOfEntity(Entity entity) {
		return m_Components[m_EntityIDToComponentIndex[entity.ID]];
	}

	template<typename T>
	inline void ComponentPool<T>::AddComponent(Entity entity) {
		m_EntityIDToComponentIndex[entity.ID] = m_Components.size();
		m_Components.emplace_back();
	}
}