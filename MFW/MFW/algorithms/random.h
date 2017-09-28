#pragma once

#include <stdio.h>
#include <stdint.h>

namespace MFWAlg {
	/**
	 * Linear congruential generator
	 * [0, 4294967295]
	 */
	static uint32_t LCG() {
		static uint32_t a = 1664525U;
		static uint32_t c = 1013904223U;
		static uint32_t X0 = 0;

		X0 = a*X0+c;
		return X0;
	}
}


