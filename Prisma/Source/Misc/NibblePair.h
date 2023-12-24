#pragma once

namespace Polyma {
	class NibblePair {
		unsigned char m_Value;

	public:
		NibblePair(unsigned char a, unsigned char b);

		unsigned char GetA() const;
		void SetA(unsigned char a);

		unsigned char GetB() const;
		void SetB(unsigned char b);
	};
}