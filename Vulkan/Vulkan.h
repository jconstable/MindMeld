#pragma once
#include "../Engine/Application.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>

#include "Pipeline.h"
#include "../Engine/Structures/Entity.h"
#include "Structures\VulkanMesh.h"

namespace VulkanImpl {
	class VulkanWrapper
	{
	public:
		VulkanWrapper();
		void createInstance(VkInstance& instance, GLFWwindow* window, MindMeld::ApplicationInfo& graphicsInfo);
		void cleanup();

		void drawEntities(const std::vector<MindMeld::Structures::Entity*> entities);
		void cleanupEntities(const std::vector<MindMeld::Structures::Entity*> entities);

	private:
		bool checkValidationLayerSupport();
		void setupDebugCallback();
		void pickPhysicalDevice();
		void createLogicalDevice();
		void createSurface();
		void createSwapChain();
		void createSwapChainImageViews();
		void createGraphicsPipelines();
		void createCommandPool();
		void createSyncObjects();
		void createDepthResources();

		void beginRendering();
		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
		void drawMesh(Pipeline* pipeline, Structures::VulkanMesh* mesh, std::vector<const VkCommandBuffer*>& outBuffers, size_t frame);
		void endRendering();



		MindMeld::ApplicationInfo m_appInfo;

		GLFWwindow * m_window;
		VkInstance m_instance;
		VkDebugUtilsMessengerEXT m_callback;

		VkSurfaceKHR m_surface;

		VkViewport m_viewport;
		VkRect2D m_scissor;

		VkPhysicalDevice m_physicalDevice;
		VkDevice m_logicalDevice;
		VkQueue m_graphicsQueue;
		VkQueue m_presentQueue;

		VkExtent2D m_swapExtent;
		VkSwapchainKHR m_swapChain;
		std::vector<VkImage> m_swapChainImages;
		VkFormat m_swapChainImageFormat;
		VkExtent2D m_swapChainExtent;

		std::vector<VkImageView> m_swapChainImageViews;
		std::vector<Pipeline*> m_pipelines;

		VkCommandPool m_commandPool;

		VkFormat m_depthFormat;
		VkImage m_depthImage;
		VkDeviceMemory m_depthImageMemory;
		VkImageView m_depthImageView;

		std::vector<VkSemaphore> m_imageAvailableSemaphores;
		std::vector<VkSemaphore> m_renderFinishedSemaphores;
		std::vector<VkFence> m_inFlightFences;
		size_t m_currentFrame = 0;
	};
}