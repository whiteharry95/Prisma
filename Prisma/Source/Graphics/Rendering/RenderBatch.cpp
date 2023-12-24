#include "RenderBatch.h"

#include <glad/glad.h>

namespace Prisma::Graphics {
	unsigned short RenderBatch::MaxUniqueTextureGLIDCount = 0;

	RenderBatch::RenderBatch(GLID vertexArrayGLID, GLID vertexBufferGLID, GLID elementBufferGLID)
		: m_VertexArrayGLID(vertexArrayGLID), m_VertexBufferGLID(vertexBufferGLID), m_ElementBufferGLID(elementBufferGLID) {
	}

	RenderBatch::~RenderBatch() {
		glDeleteBuffers(1, &m_ElementBufferGLID);
		glDeleteBuffers(1, &m_VertexBufferGLID);

		glDeleteVertexArrays(1, &m_VertexArrayGLID);
	}

	void RenderBatch::Clear() {
		m_UniqueTextureGLIDs.clear();
		m_RenderCount = 0;
	}
}