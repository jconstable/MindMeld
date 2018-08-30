#pragma once

#ifdef DEBUG
#define RUN_WITH_TRY(x)  \
try { \
	x \
} catch (const std::exception& e) { \
	std::cerr << e.what() << std::endl; \
	return EXIT_FAILURE; \
}
#else
#define RUN_WITH_TRY(x) x
#endif