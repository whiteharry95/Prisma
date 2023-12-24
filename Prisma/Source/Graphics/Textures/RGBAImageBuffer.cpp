#include "RGBAImageBuffer.h"

#include "../../Debugging.h"

namespace Prisma::Graphics {
	RGBAImageBuffer::RGBAImageBuffer(unsigned short width, unsigned short height) : m_Width(width), m_Height(height) {
		m_Buffer = new unsigned char[width * 4 * height];
	}

	RGBAImageBuffer::~RGBAImageBuffer() {
		delete[] m_Buffer;
	}

	Color RGBAImageBuffer::GetPixel(unsigned short x, unsigned short y) const {
		if (x < 0 || y < 0 || x >= m_Width || y >= m_Height) {
			Debugging::Log("Attempting to retrieve a pixel outside the bounds of an RGBA image buffer");
			return { };
		}

		unsigned int index = (y * m_Width * 4) + (x * 4);
		return { m_Buffer[index], m_Buffer[index + 1], m_Buffer[index + 2], m_Buffer[index + 3] };
	}

	void RGBAImageBuffer::SetPixel(unsigned short x, unsigned short y, Color color) {
		if (x < 0 || y < 0 || x >= m_Width || y >= m_Height) {
			Debugging::Log("Attempting to set a pixel outside the bounds of an RGBA image buffer");
			return;
		}

		unsigned int index = (y * m_Width * 4) + (x * 4);

		m_Buffer[index] = color.R;
		m_Buffer[index + 1] = color.G;
		m_Buffer[index + 2] = color.B;
		m_Buffer[index + 3] = color.A;
	}

	void RGBAImageBuffer::ClearPixels(Color color) {
		for (int i = 0; i < m_Width * 4 * m_Height; i += 4) {
			m_Buffer[i] = color.R;
			m_Buffer[i + 1] = color.G;
			m_Buffer[i + 2] = color.B;
			m_Buffer[i + 3] = color.A;
		}
	}
}