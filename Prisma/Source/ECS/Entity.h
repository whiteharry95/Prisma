#pragma once

#include <unordered_map>

namespace Prisma::ECS {
	typedef unsigned short EntityID;

	struct Entity {
		EntityID ID;

		Entity(EntityID id);

		bool operator==(const Entity &other) {
			return ID == other.ID;
		}
	};
}

namespace std {
	template<>
	struct hash<Prisma::ECS::Entity> {
		std::size_t operator()(const Prisma::ECS::Entity &entity) const {
			return std::hash<Prisma::ECS::EntityID>()(entity.ID);
		}
	};
}