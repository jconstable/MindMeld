
#include "Mesh.h"

namespace MindMeld {
	namespace Structures {
		uint32_t MindMeld::Structures::Mesh::getVertexCount() const
		{
			return (uint32_t)m_vertices.size();
		}

		const MindMeld::Structures::Vertex* MindMeld::Structures::Mesh::getVertices() const
		{
			if (getVertexCount() == 0)
			{
				return nullptr;
			}

			return m_vertices.data();
		}

		uint32_t MindMeld::Structures::Mesh::getIndexCount() const
		{
			return (uint32_t)m_indices.size();
		}

		const uint32_t* MindMeld::Structures::Mesh::getIndices() const
		{
			return m_indices.data();
		}
	}
}