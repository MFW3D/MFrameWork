#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

namespace MFWAlg {
	/**
	 * shuffle the 'list' of length 'len'
	 */
	template<typename T>
		static void shuffle(T * list, int len) {
			srand(time(NULL));
			int i = len, j;
			T temp;

			if ( i == 0 ) return;
			while ( --i ) {
				j = rand() % (i+1);
				temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}
		}
}

