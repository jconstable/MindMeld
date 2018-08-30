#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Entity.h"

namespace MindMeld {
	namespace Structures {
		Entity::Entity(Mesh* mesh)
		{
			m_mesh = mesh;
		}

		void Entity::setMesh(Mesh* mesh)
		{
			m_mesh = mesh;
		}

		Mesh* Entity::getMesh()
		{
			return m_mesh;
		}
	}
}