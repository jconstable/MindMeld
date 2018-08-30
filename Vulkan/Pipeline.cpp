#include <vector>

#include "Pipeline.h"
#include "Utils.h"


namespace VulkanImpl
{
	void Pipeline::createPipeline(VkDevice& logicalDevice, VkViewport& viewport, VkRect2D& scissor, VkFormat imageFormat) {
		throw std::runtime_error("Pipeline method createPipeline must be implemented");
	}

	void Pipeline::createFrameBuffer(VkDevice& logicalDevice, VkImageView& imageView, VkImageView& depthImageView, VkExtent2D& extents) {
		throw std::runtime_error("Pipeline method createFrameBuffer must be implemented");
	}

	void Pipeline::createCommandBuffers(VkDevice& logicalDevice, VkCommandPool& pool)
	{
		throw std::runtime_error("Pipeline method createCommandBuffers must be implemented");

		VkCommandBuffer buffer = {};
		m_commandBuffers.push_back(buffer);
	}

	void Pipeline::destroyPipeline(VkDevice& logicalDevice, VkCommandPool& commandPool) {
		throw std::runtime_error("Pipeline method destroyPipeline must be implemented");
	}

	void Pipeline::beginRendering(size_t resourcesIndex)
	{
		throw std::runtime_error("Pipeline method beginRendering must be implemented");
	}

	void Pipeline::drawMesh(VkDevice& logicalDevice, size_t resourcesIndex, const MindMeld::Structures::Mesh* mesh, std::vector<const VkCommandBuffer*>& outBuffers) const
	{
		throw std::runtime_error("Pipeline method drawMesh must be implemented");
	}

	void Pipeline::endRendering(size_t resourcesIndex)
	{
		throw std::runtime_error("Pipeline method endRendering must be implemented");
	}

	void Pipeline::createShaders(VkDevice& logicalDevice, VulkanImpl::ShaderInfo* shaderInfos, int infoCount)
	{
		VulkanImpl::ShaderInfo* incrInfos = shaderInfos;

		size_t originalSize = m_shaderModules.size();
		m_shaderModules.resize(originalSize + infoCount);
		m_shaderStages.resize(originalSize + infoCount);

		for (int i = 0; i < infoCount; i++)
		{
			size_t index = originalSize + i;
			try {
				VulkanImpl::ShaderInfo& info = (*incrInfos);
				createShader(logicalDevice, info.filePath, m_shaderModules[index]);

				m_shaderStages[index] = createShaderStage(m_shaderModules[index], info.flagBits);

				incrInfos++;
			}
			catch (std::exception& e)
			{
				std::cerr << e.what() << std::endl;
			}
		}
	}

	void Pipeline::createShader(VkDevice& logicalDevice, const char* shaderPath, VkShaderModule& destModule)
	{
		std::vector<char> shaderCode = VulkanImpl::Utils::readFile(shaderPath);
		try {
			destModule = VulkanImpl::Utils::createShaderModule(logicalDevice, shaderCode);
		}
		catch (const std::exception& e)
		{
			std::ostringstream s;
			s << "Unable to create shader module: " << shaderPath << e.what();
			throw std::runtime_error(s.str());
		}
	}

	VkPipelineShaderStageCreateInfo Pipeline::createShaderStage(VkShaderModule& module, VkShaderStageFlagBits stage)
	{
		VkPipelineShaderStageCreateInfo createInfo = {};

		createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		createInfo.stage = stage;
		createInfo.module = module;
		createInfo.pName = "main";

		return createInfo;
	}

	size_t Pipeline::getFramebufferCount() {
		return m_frameBuffers.size();
	}

	VkFramebuffer& Pipeline::getFramebuffer(uint32_t index)
	{
#ifdef DEBUG
		if (index >= getFramebufferCount())
		{
			throw std::runtime_error("Requested framebuffer at index outside range");
		}
#endif

		return m_frameBuffers[index]; 
	}

	size_t Pipeline::getCommandBufferCount()
	{
		return m_commandBuffers.size();
	}

	VkCommandBuffer& Pipeline::getCommandBuffer(uint32_t index)
	{
		throw std::runtime_error("Pipeline method endRendering must be implemented");

		return m_commandBuffers[index];
	}

	void Pipeline::setClear(bool doClear, VkClearValue clearColor)
	{
		m_doClear = doClear;

		m_clearColor = clearColor;
	}
}