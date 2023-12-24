#include "RenderLayer.h"

#include <algorithm>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../../Application.h"

namespace Prisma::Graphics {
	void RenderLayer::Init(unsigned short maxRenderCountPerBatch, const TextureManager *textureManager, const FontManager *fontManager, const ShaderManager *shaderManager) {
		m_TextureManager = textureManager;
		m_FontManager = fontManager;
		m_ShaderManager = shaderManager;

		m_MaxRenderCountPerBatch = maxRenderCountPerBatch;
	}

	void RenderLayer::Update() {
		if (m_RenderBatches.size() > 0) {
			m_LastRenderBatchPopTime++;

			if (m_LastRenderBatchPopTime >= m_LastRenderBatchPopTimeMax) {
				delete m_RenderBatches[m_RenderBatches.size() - 1];
				m_RenderBatches.pop_back();

				m_LastRenderBatchPopTime = 0;
			}
		}
	}

	void RenderLayer::Render(const Window &window) {
		if (m_RenderBatchCount == 0) {
			return;
		}

		GLID textureShaderProgramGLID = m_ShaderManager->GetShaderProgram(0).GetGLID();

		glUseProgram(textureShaderProgramGLID);

		glm::mat4 viewMatrix(1.f);

		glm::vec2 windowSize = window.GetSize();
		glm::mat4 projectionMatrix = glm::ortho(0.f, windowSize.x, windowSize.y, 0.f, -1.f, 1.f);

		glUniformMatrix4fv(glGetUniformLocation(textureShaderProgramGLID, "u_ViewMatrix"), 1, GL_FALSE, &viewMatrix[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(textureShaderProgramGLID, "u_ProjectionMatrix"), 1, GL_FALSE, &projectionMatrix[0][0]);

		for (int i = 0; i < m_RenderBatchCount; i++) {
			unsigned int textureCount = m_RenderBatches[i]->GetUniqueTextureIDCount();

			for (int j = 0; j < textureCount; j++) {
				glActiveTexture(GL_TEXTURE0 + j);
				glBindTexture(GL_TEXTURE_2D, m_RenderBatches[i]->GetUniqueTextureGLID(j));
			}

			if (textureCount > 0) {
				int *samplers = new int[textureCount];

				for (int j = 0; j < textureCount; j++) {
					samplers[j] = j;
				}

				glUniform1iv(glGetUniformLocation(textureShaderProgramGLID, "u_Samplers"), textureCount, samplers);

				delete[] samplers;
			}

			glBindVertexArray(m_RenderBatches[i]->GetVertexArrayGLID());
			glDrawElements(GL_TRIANGLES, ElementBufferElementCountPerRender * m_RenderBatches[i]->GetRenderCount(), GL_UNSIGNED_SHORT, nullptr);
		}
	}

	void RenderLayer::Clean() {
		for (RenderBatch *renderBatch : m_RenderBatches) {
			delete renderBatch;
		}
	}

	void RenderLayer::Clear() {
		for (RenderBatch *renderBatch : m_RenderBatches) {
			renderBatch->Clear();
		}

		m_RenderBatchCount = 0;
		m_UniqueTextureIDCount = 0;
	}

	void RenderLayer::Submit(const Texture &texture, SourceRectangle sourceRect, const Math::Shapes::Rectangle &destinationRect, float rotation, glm::vec2 origin, float opacity) {
		unsigned int batchIndex;
		unsigned int textureSlotIndex;

		bool found = false;

		for (int i = 0; i < m_RenderBatchCount; i++) {
			unsigned int uniqueTextureIDCount = m_RenderBatches[i]->GetUniqueTextureIDCount();

			if (m_RenderBatches[i]->GetRenderCount() < m_MaxRenderCountPerBatch && uniqueTextureIDCount < RenderBatch::MaxUniqueTextureGLIDCount) {
				unsigned int uniqueTextureIDIndex = m_RenderBatches[i]->GetUniqueTextureGLIDIndex(texture.GetGLID());

				if (uniqueTextureIDIndex == m_RenderBatches[i]->GetUniqueTextureIDCount()) { // If the texture ID is not found
					if (i == m_RenderBatchCount - 1) {
						batchIndex = i;
						textureSlotIndex = m_RenderBatches[i]->GetUniqueTextureIDCount();

						m_RenderBatches[i]->AddUniqueTextureGLID(texture.GetGLID());
						m_UniqueTextureIDCount++;

						found = true;

						break;
					}
				} else {
					batchIndex = i;
					textureSlotIndex = uniqueTextureIDIndex;

					found = true;

					break;
				}
			}
		}

		if (found) {
			if (batchIndex == m_RenderBatches.size() - 1) {
				m_LastRenderBatchPopTime = 0;
			}
		} else {
			batchIndex = m_RenderBatchCount;
			textureSlotIndex = 0;

			m_RenderBatchCount++;
			m_UniqueTextureIDCount++;

			if (m_RenderBatchCount - 1 < m_RenderBatches.size()) {
				m_RenderBatches[m_RenderBatchCount - 1]->AddUniqueTextureGLID(texture.GetGLID());
			} else {
				unsigned int vertexArrayID;
				glGenVertexArrays(1, &vertexArrayID);
				glBindVertexArray(vertexArrayID);

				float *vertexBuffer = new float[VertexBufferElementCountPerRender * m_MaxRenderCountPerBatch];
				unsigned short *elementBuffer = new unsigned short[ElementBufferElementCountPerRender * m_MaxRenderCountPerBatch];

				unsigned int vertexBufferID;
				glGenBuffers(1, &vertexBufferID);
				glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
				glBufferData(GL_ARRAY_BUFFER, VertexBufferElementCountPerRender * m_MaxRenderCountPerBatch * sizeof(float), vertexBuffer, GL_STATIC_DRAW);

				unsigned int elementBufferID;
				glGenBuffers(1, &elementBufferID);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, ElementBufferElementCountPerRender * m_MaxRenderCountPerBatch * sizeof(unsigned short), elementBuffer, GL_STATIC_DRAW);

				unsigned char stride = (VertexBufferElementCountPerRender / 4) * sizeof(float);

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, stride, (void *)0);

				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void *)(1 * sizeof(float)));

				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void *)(3 * sizeof(float)));

				glEnableVertexAttribArray(3);
				glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, stride, (void *)(5 * sizeof(float)));

				glEnableVertexAttribArray(4);
				glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, stride, (void *)(7 * sizeof(float)));

				glEnableVertexAttribArray(5);
				glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, stride, (void *)(8 * sizeof(float)));

				glEnableVertexAttribArray(6);
				glVertexAttribPointer(6, 1, GL_FLOAT, GL_FALSE, stride, (void *)(10 * sizeof(float)));

				glBindVertexArray(0);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				delete[] elementBuffer;
				delete[] vertexBuffer;

				RenderBatch *batch = new RenderBatch(vertexArrayID, vertexBufferID, elementBufferID);
				batch->AddUniqueTextureGLID(texture.GetGLID());

				m_RenderBatches.push_back(batch);

				m_LastRenderBatchPopTime = 0;
			}
		}

		// Defining the vertices and elements to add
		if (sourceRect.Width == 0 && sourceRect.Height == 0) {
			sourceRect.Width = texture.GetWidth();
			sourceRect.Height = texture.GetHeight();
		}

		float vertices[] = {
			textureSlotIndex, static_cast<float>(sourceRect.X) / texture.GetWidth(), static_cast<float>(sourceRect.Y) / texture.GetHeight(), -origin.x, -origin.y, destinationRect.GetPosition().x, destinationRect.GetPosition().y, rotation, destinationRect.GetSize().x, destinationRect.GetSize().y, opacity,
			textureSlotIndex, static_cast<float>(sourceRect.X + sourceRect.Width) / texture.GetWidth(), static_cast<float>(sourceRect.Y) / texture.GetHeight(), 1.f - origin.x, -origin.y, destinationRect.GetPosition().x, destinationRect.GetPosition().y, rotation, destinationRect.GetSize().x, destinationRect.GetSize().y, opacity,
			textureSlotIndex, static_cast<float>(sourceRect.X + sourceRect.Width) / texture.GetWidth(), static_cast<float>(sourceRect.Y + sourceRect.Height) / texture.GetHeight(), 1.f - origin.x, 1.f - origin.y, destinationRect.GetPosition().x, destinationRect.GetPosition().y, rotation, destinationRect.GetSize().x, destinationRect.GetSize().y, opacity,
			textureSlotIndex, static_cast<float>(sourceRect.X) / texture.GetWidth(), static_cast<float>(sourceRect.Y + sourceRect.Height) / texture.GetHeight(), -origin.x, 1.f - origin.y, destinationRect.GetPosition().x, destinationRect.GetPosition().y, rotation, destinationRect.GetSize().x, destinationRect.GetSize().y, opacity
		};

		unsigned short elements[] = {
			0, 1, 2,
			2, 3, 0
		};

		for (int i = 0; i < ElementBufferElementCountPerRender; i++) {
			elements[i] += 4 * m_RenderBatches[batchIndex]->GetRenderCount();
		}

		// Submitting the vertex and element data
		glBindVertexArray(m_RenderBatches[batchIndex]->GetVertexArrayGLID());

		glBindBuffer(GL_ARRAY_BUFFER, m_RenderBatches[batchIndex]->GetVertexBufferGLID());
		glBufferSubData(GL_ARRAY_BUFFER, VertexBufferElementCountPerRender * m_RenderBatches[batchIndex]->GetRenderCount() * sizeof(float), VertexBufferElementCountPerRender * sizeof(float), vertices);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderBatches[batchIndex]->GetElementBufferGLID());
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, ElementBufferElementCountPerRender * m_RenderBatches[batchIndex]->GetRenderCount() * sizeof(unsigned short), ElementBufferElementCountPerRender * sizeof(unsigned short), elements);

		m_RenderBatches[batchIndex]->IncrementRenderCount();
	}
}