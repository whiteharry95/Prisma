#pragma once

#include <unordered_map>

namespace Prisma::ECS {
	typedef unsigned short EntityID;

	struct Entity {
		EntityID ID;

		Entity(EntityID id);
	};
}