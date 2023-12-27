#pragma once

#include "../Color.h"

namespace Prisma::Graphics {
	/// <summary>
	/// A wrapper for an RGBA image buffer, which simplifies the process of reading from and writing to specific pixels
	/// </summary>
	class RGBAImageBuffer {
		unsigned char *m_Buffer;

		unsigned short m_Width = 0;
		unsigned short m_Height = 0;

	public:
		RGBAImageBuffer(unsigned short width, unsigned short height);
		~RGBAImageBuffer();

		unsigned char *GetRaw() const {
			return m_Buffer;
		}

		unsigned short GetWidth() const {
			return m_Width;
		}

		unsigned short GetHeight() const {
			return m_Height;
		}

		Color GetPixel(unsigned short x, unsigned short y) const;
		void SetPixel(unsigned short x, unsigned short y, Color color);

		void ClearPixels(Color color = { });
	};
}