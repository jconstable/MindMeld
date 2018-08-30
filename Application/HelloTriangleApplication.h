#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "../Vulkan/Vulkan.h"
#include "Level/Level.h"

namespace HelloTriangle {
	class HelloTriangleApplication {
	public:
		HelloTriangleApplication();

		void initGraphics();
		void initWindow();
		int mainLoop();
		void cleanup();

		void setLevel(Level::Level* level);
	private:
		GLFWwindow * m_window;
		VkInstance m_instance;
		Level::Level* m_currentLevel;

		VulkanImpl::VulkanWrapper m_wrapper;
	};
}