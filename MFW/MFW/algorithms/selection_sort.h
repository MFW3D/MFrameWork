#pragma once

#include <assert.h>
#include <generic.h>

namespace MFWAlg {
	template<typename T>
		static void SelectionSort(T list[], int start, int end) {
			int i,j;
			int iMin;

			assert(start <= end);

			for(j = start; j <= end-1; j++) {
				// assume the min is the first element */
				iMin = j;
				// test against elements after i to find the smallest
				for(i = j+1; i <= end; i++) {
					if (list[i] < list[iMin]) {
						iMin = i;
					}
				}

				// iMin is the index of the minimum element. Swap it with the current position
				if (iMin != j) {
					swap(list[j], list[iMin]);
				}
			}
		}
}

