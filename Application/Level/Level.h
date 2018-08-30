#pragma once

#include <vector>

#include "../Engine/Structures/Entity.h"
#include "../../Vulkan/Structures/VulkanMesh.h"

namespace HelloTriangle {
	namespace Level {
		class Level {
		public:
			Level();
			const std::vector<MindMeld::Structures::Entity*> getEntites();
			void cleanup();

		private:
			std::vector<MindMeld::Structures::Entity*> m_entities;
		};
	}
}