#pragma once

#include <vector>

#include "../../Engine/Structures/Mesh.h"

namespace VulkanImpl {
	namespace Structures {
		class VulkanMesh : public MindMeld::Structures::Mesh {
			friend class MeshCreator;
		public:
			VkBuffer& getVertexBuffer(VkPhysicalDevice& physicalDevice, VkDevice& logicalDevice);
			void destroyVertexBuffer(VkDevice& logicalDevice);


			static uint32_t findMemoryType(VkPhysicalDevice& physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);
		protected:

			VkDeviceMemory m_vertexBufferMemory;
			VkBuffer m_vertexBuffer;
		};

		class MeshCreator {
		public:
			static VulkanMesh* createMesh(std::vector<MindMeld::Structures::Vertex>& vertices,
				std::vector<uint32_t>& indices,
				uint32_t startVertex,
				uint32_t startIndex
			)
			{
				VulkanMesh* mesh = new VulkanMesh();
				mesh->m_vertices = std::vector<MindMeld::Structures::Vertex>(vertices);
				mesh->m_indices = std::vector<uint32_t>(indices);
				mesh->m_startVertex = startVertex;
				mesh->m_startIndex = startIndex;
				return mesh;
			}
		};
	}
}
