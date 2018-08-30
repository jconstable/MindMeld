#pragma once

#include <functional>
#include <exception>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Vulkan.h"

namespace VulkanImpl
{
	class Utils
	{
	public:
		static std::vector<char> readFile(const std::string& filename);
		static VkShaderModule createShaderModule(VkDevice& virtualDevice, const std::vector<char>& code);
	};
}
