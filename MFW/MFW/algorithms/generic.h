#pragma once

#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>

#include "gb18030.h"
#include "byteorder.h"


#define Max(a, b) ( (a > b) ? a : b )
#define Min(a, b) ( (a < b) ? a : b )

#define RANDOM_INIT()	srand(time(NULL))
#define RANDOM(L, R)	(L + rand() % ((R) - (L) + 1)) // gen a random integer in [L, R]

namespace MFWAlg {
	/**
	 * swap 2-element, orignal value 
	 */
	template<typename T>
		static inline void swap(T &x, T &y)
		{
			T _t(x);
			x = y;
			y = _t;
		}

	/**
	 * print all of the elements in `list` with size `n`
	 */
	template<typename T>
		static void printlist(T & list,int count) {
			int i;
			for(i=0;i<count;i++)
				printf("%d\t ",list[i]);
			printf("\n");
		}

	/**
	 * pass in array with *len
	 * return new length
	 */
	template<typename T>
		static uint32_t remove_dup(T a[], uint32_t len) {
			uint32_t i;
			uint32_t newlen = len;
			for (i=0; i<newlen; i++) {
				T key = a[i];
				uint32_t j;
				for (j=i+1;j<newlen;j++) {
					if(key == a[j]) {
						/* found dup, move left one position. */ 
						uint32_t k;
						for (k=j;k<newlen-1;k++) {
							a[k] = a[k+1];
						}
						newlen--;
					}
				}
			}

			return newlen;
		}
}


