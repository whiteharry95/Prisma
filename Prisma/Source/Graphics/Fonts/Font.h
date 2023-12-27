#pragma once

#include <array>

#include "FontFace.h"
#include "../Textures/Texture.h"
#include "../../Debugging.h"
#include "../SourceRectangle.h"

namespace Prisma::Graphics {
	typedef unsigned char FontID;

	class Font {
		static constexpr unsigned char CharacterRangeStart = 32;
		static constexpr unsigned char CharacterRangeEnd = 126;

		FontID m_ID = 0;
		FontFaceID m_FaceID = 0;

		unsigned short m_PointSize = 0;

		Texture *m_Texture;

		std::array<SourceRectangle, CharacterRangeEnd - CharacterRangeStart + 1> m_CharacterSourceRects;

	public:
		enum class HorizontalAlignment : unsigned char {
			Left,
			Center,
			Right
		};

		enum class VerticalAlignment : unsigned char {
			Top,
			Middle,
			Bottom
		};

		Font(FontID id, const FontFace &face, unsigned short pointSize);

		void Clean();

		FontID GetID() const {
			return m_ID;
		}

		FontFaceID GetFaceID() const {
			return m_FaceID;
		}

		unsigned short GetPointSize() const {
			return m_PointSize;
		}

		const Texture &GetTexture() const {
			return *m_Texture;
		}

		SourceRectangle GetSourceRectOfCharacter(unsigned char character) const {
			if (character < CharacterRangeStart || character > CharacterRangeEnd) {
				Debugging::LogError("Attempting to retrieve the source rectangle of an out-of-range character");
				return { };
			}

			return m_CharacterSourceRects[character - CharacterRangeStart];
		}
	};
}