#pragma once

#include <stdint.h>

namespace MFWAlg {
	/**
	 * hash a string into integer
	 * using java's hashCode() implementation
	 */
	static uint32_t hash_string(const char * str, uint32_t len) {
		uint32_t hash=0;	
		uint32_t i;	
		for (i=0;i<len;i++) {
			hash = 31*hash + (unsigned char)str[i];
		}

		return hash;
	}

	static uint32_t hash_fnv1a(const char * str, uint32_t len) {
		uint32_t prime = 16777619U;
		uint32_t hash = 2166136261U;

		for (uint32_t  i=0;i<len;i++) {
			hash = hash ^ str[i];
			hash = hash * prime;
		}

		return hash;
	}
}


