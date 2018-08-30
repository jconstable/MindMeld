#include "VulkanMesh.h"

namespace VulkanImpl {
	namespace Structures {
		uint32_t VulkanMesh::findMemoryType(VkPhysicalDevice& physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties)
		{
			VkPhysicalDeviceMemoryProperties memPropertiesphysicalDevice;
			vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memPropertiesphysicalDevice);

			for (uint32_t i = 0; i < memPropertiesphysicalDevice.memoryTypeCount; i++) {
				if ((typeFilter & (1 << i)) && (memPropertiesphysicalDevice.memoryTypes[i].propertyFlags & properties) == properties) {
					return i;
				}
			}

			throw std::runtime_error("failed to find suitable memory type!");
		}

		VkBuffer& VulkanMesh::getVertexBuffer(VkPhysicalDevice& physicalDevice, VkDevice& logicalDevice)
		{
			if (m_vertexBuffer != VK_NULL_HANDLE)
			{
				return m_vertexBuffer;
			}

			MindMeld::Structures::Vertex& v = m_vertices[0];

			VkBufferCreateInfo bufferInfo = {};
			bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			bufferInfo.size = sizeof(v) * m_vertices.size();
			bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
			bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;


			if (vkCreateBuffer(logicalDevice, &bufferInfo, nullptr, &m_vertexBuffer) != VK_SUCCESS) {
				throw std::runtime_error("Failed to create vertex buffer!");
			}

			VkMemoryRequirements memRequirements;
			vkGetBufferMemoryRequirements(logicalDevice, m_vertexBuffer, &memRequirements);

			VkMemoryAllocateInfo allocInfo = {};
			allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			allocInfo.allocationSize = memRequirements.size;
			allocInfo.memoryTypeIndex = findMemoryType(physicalDevice, memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

			auto result = vkAllocateMemory(logicalDevice, &allocInfo, nullptr, &m_vertexBufferMemory);
			if (result != VK_SUCCESS) {
				throw std::runtime_error("Failed to allocate vertex buffer memory!");
			}

			vkBindBufferMemory(logicalDevice, m_vertexBuffer, m_vertexBufferMemory, 0);

			void* data;
			vkMapMemory(logicalDevice, m_vertexBufferMemory, 0, bufferInfo.size, 0, &data);
			memcpy(data, m_vertices.data(), (size_t)bufferInfo.size);
			vkUnmapMemory(logicalDevice, m_vertexBufferMemory);

			return m_vertexBuffer;
		}

		void VulkanMesh::destroyVertexBuffer(VkDevice& logicalDevice)
		{
			vkFreeMemory(logicalDevice, m_vertexBufferMemory, nullptr);
			vkDestroyBuffer(logicalDevice, m_vertexBuffer, nullptr);

			m_vertexBuffer = VK_NULL_HANDLE;
			m_vertexBufferMemory = VK_NULL_HANDLE;
		}
	}
}