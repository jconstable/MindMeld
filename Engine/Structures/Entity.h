#pragma once

#include <glm/glm.hpp>

#include <vector>

#include "Mesh.h"

namespace MindMeld {
	namespace Structures {
		class Entity {
		public:
			Entity(Mesh* mesh);
			void setMesh(Mesh* mesh);
			virtual Mesh* getMesh();
			virtual ~Entity() = default;
		protected:
			Mesh* m_mesh;
			glm::vec3 m_translation;
			glm::vec4 m_rotation;
			glm::vec3 m_scale;
		};
	}
}
