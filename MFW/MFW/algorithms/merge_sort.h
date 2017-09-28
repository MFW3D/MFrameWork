#pragma once

namespace MFWAlg {
	/**
	 * Merge functions merges the two sorted parts. Sorted parts will be from [left, mid] and [mid+1, right].
	 */
	template<typename T>
		static void merge_(T *array, int left, int mid, int right) {
			/*We need a Temporary array to store the new sorted part*/
			T tempArray[right-left+1];
			int pos=0,lpos = left,rpos = mid + 1;
			while(lpos <= mid && rpos <= right) {
				if(array[lpos] < array[rpos]) {
					tempArray[pos++] = array[lpos++];
				}
				else {
					tempArray[pos++] = array[rpos++];
				}
			}
			while(lpos <= mid)  tempArray[pos++] = array[lpos++];
			while(rpos <= right)tempArray[pos++] = array[rpos++];
			int iter;
			/* Copy back the sorted array to the original array */
			for(iter = 0;iter < pos; iter++) {
				array[iter+left] = tempArray[iter];
			}
			return;
		}

	/**
	 * sort an array from left->right 
	 */
	template<typename T>
		static void merge_sort(T *array, int left, int right) {
			int mid = (left+right)/2;
			/* We have to sort only when left<right because when left=right it is anyhow sorted*/
			if(left<right) {
				/* Sort the left part */
				merge_sort(array,left,mid);
				/* Sort the right part */
				merge_sort(array,mid+1,right);
				/* Merge the two sorted parts */
				merge_(array,left,mid,right);
			}
		}

}



