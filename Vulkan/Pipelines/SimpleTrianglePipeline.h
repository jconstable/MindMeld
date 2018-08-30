#pragma once
#include <vector>
#include "../Pipeline.h"


namespace VulkanImpl {
	namespace Pipelines
	{
		class SimpleTrianglePipeline : public Pipeline
		{
		public:
			SimpleTrianglePipeline() {};
			virtual void createPipeline(VkDevice& logicalDevice, VkViewport& viewport, VkRect2D& scissor, VkFormat imageFormat, VkFormat depthFormat);
			virtual void createFrameBuffer(VkDevice& logicalDevice, VkImageView& imageView, VkImageView& depthImageView, VkExtent2D& extents);
			virtual void createCommandBuffers(VkDevice& logicalDevice, VkCommandPool& pool);
			virtual void destroyPipeline(VkDevice& logicalDevice, VkCommandPool& commandPool);

			virtual void beginRendering(size_t resourcesIndex);
			virtual void endRendering(size_t resourcesIndex);

			virtual VkCommandBuffer& getCommandBuffer(uint32_t index);
			
		private:
			void createRenderPass(VkDevice& logicalDevice, VkFormat imageFormat, VkFormat depthFormat);

			void beginRenderPass(size_t resourceIndex);
			void endRenderPass(size_t resourceIndex);
			
			VkPipelineLayout m_pipelineLayout;
			VkRenderPass m_renderPass;
			VkExtent2D m_extents;

			VkPipeline m_graphicsPipeline;
		};
	}
};