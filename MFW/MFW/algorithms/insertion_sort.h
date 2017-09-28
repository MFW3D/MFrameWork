#pragma once

namespace MFWAlg {
	/**
	 * insertion sort an array
	 */
	template<typename T>
		static void insertion_sort(T *array , int number_of_elements) {
			int iter,jter;
			for(iter=1;iter<number_of_elements;iter++) {
				T current_element = array[iter];
				jter = iter-1;
				while(jter>=0 && array[jter] > current_element) {
					array[jter+1] = array[jter];
					jter--;
				}
				array[jter+1] = current_element;
			}
		}
}


