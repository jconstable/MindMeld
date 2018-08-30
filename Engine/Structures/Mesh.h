#pragma once

#include <vector>

#include "Vertex.h"

namespace MindMeld {
	namespace Structures {
		class Mesh {
			friend class MeshCreator;
		public:
			virtual uint32_t getVertexCount() const;
			virtual const Vertex* getVertices() const;

			virtual uint32_t getIndexCount() const;
			virtual const uint32_t* getIndices() const;

			uint32_t getStartVertex() const { return m_startVertex; }
			uint32_t getStartIndex() const { return m_startIndex; }

			virtual ~Mesh() = default;
		protected:
			Mesh() {};
			std::vector<Vertex> m_vertices;
			std::vector<uint32_t> m_indices;
			uint32_t m_startVertex = 0;
			uint32_t m_startIndex = 0;
		};

		class MeshCreator {
		public:
			static Mesh* createMesh(std::vector<Vertex>& vertices,
				std::vector<uint32_t>& indices,
				uint32_t startVertex,
				uint32_t startIndex
			)
			{
				Mesh* mesh = new Mesh();
				mesh->m_vertices = std::vector<Vertex>(vertices);
				mesh->m_indices = std::vector<uint32_t>(indices);
				mesh->m_startVertex = startVertex;
				mesh->m_startIndex = startIndex;
				return mesh;
			}
		};
	}
}
