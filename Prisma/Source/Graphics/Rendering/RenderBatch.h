#pragma once

#include <vector>

#include "../GLID.h"

namespace Prisma::Graphics {
	class RenderBatch {
		GLID m_VertexArrayGLID;

		GLID m_VertexBufferGLID;
		GLID m_ElementBufferGLID;

		std::vector<GLID> m_UniqueTextureGLIDs;

		unsigned short m_RenderCount;

	public:
		static unsigned short MaxUniqueTextureGLIDCount;

		RenderBatch(GLID vertexArrayGLID, GLID vertexBufferGLID, GLID elementBufferGLID);
		~RenderBatch();

		void Clear();

		GLID GetVertexArrayGLID() const {
			return m_VertexArrayGLID;
		}

		GLID GetVertexBufferGLID() const {
			return m_VertexBufferGLID;
		}

		GLID GetElementBufferGLID() const {
			return m_ElementBufferGLID;
		}

		unsigned int GetUniqueTextureGLID(unsigned int index) {
			return m_UniqueTextureGLIDs[index];
		}

		unsigned int GetUniqueTextureGLIDIndex(GLID glid) {
			if (m_UniqueTextureGLIDs.size() == 0) {
				return m_UniqueTextureGLIDs.size();
			}

			auto glidsIterator = std::find(m_UniqueTextureGLIDs.begin(), m_UniqueTextureGLIDs.end(), glid);
			return std::distance(m_UniqueTextureGLIDs.begin(), glidsIterator);
		}

		unsigned int GetUniqueTextureIDCount() {
			return m_UniqueTextureGLIDs.size();
		}

		void AddUniqueTextureGLID(GLID glid) {
			m_UniqueTextureGLIDs.push_back(glid);
		}

		unsigned short GetRenderCount() const {
			return m_RenderCount;
		}

		void IncrementRenderCount() {
			m_RenderCount++;
		}
	};
}