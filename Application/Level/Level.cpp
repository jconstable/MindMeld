#include "Level.h"

namespace HelloTriangle {
	namespace Level {
		Level::Level()
		{
			std::vector<MindMeld::Structures::Vertex> vertices;
			vertices.push_back({ { 0.0,-0.5, 0.0 }, { 1.0,0.0,0.0 } });
			vertices.push_back({ { 0.5,0.5, 0.0 }, { 0.0,1.0,0.0 } });
			vertices.push_back({ { -0.5, 0.5, 0.0 }, { 0.0,0.0,1.0 } });

			std::vector<uint32_t> indices = {
				0, 1, 2
			};
			
			VulkanImpl::Structures::VulkanMesh* m = VulkanImpl::Structures::MeshCreator::createMesh(
				vertices, 
				indices,
				(uint32_t)0,
				(uint32_t)0
			);

			MindMeld::Structures::Entity* e = new MindMeld::Structures::Entity(m);
			m_entities.push_back(e);
		}

		const std::vector<MindMeld::Structures::Entity*> Level::getEntites()
		{
			return m_entities;
		}

		void Level::cleanup()
		{
			for (auto entity : m_entities)
			{
				delete(entity);
			}

			m_entities.clear();
		}
	}
}
