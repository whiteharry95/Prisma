#pragma once

#include <string>

namespace Prisma::Debugging {
	void Log(const std::string &message);
	void LogWarning(const std::string &message, const std::string &providedBy = "");
	void LogError(const std::string &message, const std::string &providedBy = "");
}