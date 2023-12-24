#include "Debugging.h"

#include <iostream>

namespace Prisma::Debugging {
	void Log(const std::string &message) {
		std::cout << message << '\n';
	}
}