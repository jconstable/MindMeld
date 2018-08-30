#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace VulkanImpl
{
	struct ShaderInfo {
		const char* filePath;
		VkShaderStageFlagBits flagBits;
	};
}