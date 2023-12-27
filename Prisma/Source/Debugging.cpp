#include "Debugging.h"

#include <iostream>

namespace Prisma::Debugging {
	namespace {
		void LogBase(const std::string &prefix, const std::string &message, const std::string &providedBy) {
			std::cout << prefix << '"' << message << (providedBy != "" ? "\" (" + providedBy + ')' : "") << '\n';
		}
	}

	void Log(const std::string &message) {
		LogBase("", message, "");
	}

	void LogWarning(const std::string &message, const std::string &providedBy) {
		LogBase("Warning: ", message, providedBy);
	}

	void LogError(const std::string &message, const std::string &providedBy) {
		LogBase("Error: ", message, providedBy);
	}
}