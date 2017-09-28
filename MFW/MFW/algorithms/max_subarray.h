#pragma once

namespace MFWAlg {
	/**
	 * To calc the maximum subarray, and return the range.
	 */
	static void max_subarray(int arr[], int len,  int *begin, int *end) {
		int i;
		int subvalue = arr[0];
		int maxvalue = arr[0];
		*begin = 0;
		*end = 0;
		int new_begin;

		for (i = 1;i < len;i++) {
			if (subvalue > 0) {		// positive contribute to the following element
				subvalue +=	arr[i];
			} else {
				subvalue = arr[i];	// negative contribute, drop it!
				new_begin = i;		// then set the new beginning.
			}

			if (maxvalue < subvalue) {	// if a larger subarray appears, record the range
				maxvalue = subvalue;
				*begin = new_begin;
				*end = i;
			}
		}
	}
}

