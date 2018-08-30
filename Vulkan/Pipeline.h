#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "../Engine/Structures/Mesh.h"
#include "ShaderInfo.h"

namespace VulkanImpl
{
	static VkVertexInputBindingDescription getBindingDescription() {
		VkVertexInputBindingDescription bindingDescription = {};

		bindingDescription.binding = 0;
		bindingDescription.stride = (uint32_t)sizeof(MindMeld::Structures::Vertex);;
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescription;
	}

	static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
		std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions = {};

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(MindMeld::Structures::Vertex, position);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(MindMeld::Structures::Vertex, color);

		return attributeDescriptions;
	}

	class Pipeline
	{
	public:
		Pipeline() {};
		virtual void createPipeline(VkDevice& logicalDevice, VkViewport& viewport, VkRect2D& scissor, VkFormat imageFormat);
		virtual void createFrameBuffer(VkDevice& logicalDevice, VkImageView& imageView, VkImageView& depthImageView, VkExtent2D& extents);
		virtual void createCommandBuffers(VkDevice& logicalDevice, VkCommandPool& pool);
		virtual void destroyPipeline(VkDevice& logicalDevice, VkCommandPool& commandPool);

		void setClear(bool doClear, VkClearValue clearColor);
		void createShaders(VkDevice& logicalDevice, VulkanImpl::ShaderInfo* shaderInfos, int infoCount);

		virtual void beginRendering(size_t resourcesIndex);
		virtual void drawMesh(VkDevice& logicalDevice, size_t resourcesIndex, const MindMeld::Structures::Mesh* mesh, std::vector<const VkCommandBuffer*>& outBuffers) const;
		virtual void endRendering(size_t resourcesIndex);

		size_t getFramebufferCount();
		VkFramebuffer& getFramebuffer(uint32_t index);

		size_t getCommandBufferCount();
		virtual VkCommandBuffer& getCommandBuffer(uint32_t index);


		virtual ~Pipeline() = default;

	protected:
		static void createShader(VkDevice& logicalDevice, const char* shaderPath, VkShaderModule& destModule);
		static VkPipelineShaderStageCreateInfo createShaderStage(VkShaderModule& module, VkShaderStageFlagBits stage);

		std::vector<VkShaderModule> m_shaderModules;
		std::vector<VkPipelineShaderStageCreateInfo> m_shaderStages;

		std::vector<VkFramebuffer> m_frameBuffers;
		std::vector<VkCommandBuffer> m_commandBuffers;

		VkClearValue m_clearColor;
		bool m_doClear;
	};
}