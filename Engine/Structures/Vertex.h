#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <array>
#include <glm/glm.hpp>
#include <cstddef>

namespace MindMeld {
	namespace Structures {
		struct Vertex {
			glm::vec3 position;
			glm::vec3 color;
		};
	}
}