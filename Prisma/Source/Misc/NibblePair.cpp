#include "NibblePair.h"

namespace Polyma {
	NibblePair::NibblePair(unsigned char a, unsigned char b) {
		m_Value = (b << 4) | (a & 0x0F);
	}

	unsigned char NibblePair::GetA() const {
		return m_Value & 0x0F;
	}

	void NibblePair::SetA(unsigned char a) {
		m_Value = (m_Value & 0xF0) | (a & 0x0F);
	}

	unsigned char NibblePair::GetB() const {
		return m_Value >> 4;
	}

	void NibblePair::SetB(unsigned char b) {
		m_Value = (m_Value & 0x0F) | (b << 4);
	}
}