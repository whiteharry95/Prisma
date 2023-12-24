#pragma once

#include "Shape.h"

namespace Prisma::Math::Shapes {
	class Polygon : public Shape {
	public:
		bool Contains();
		bool Intersects();
	};
}