#include "2darray.h"
namespace MFWAlg {
	template <typename T = char>
	Array2D<T>::Array2D(uint32_t nrow, uint32_t ncol) {
		NR = nrow;
		NC = ncol;
		m_data = new T[nrow*ncol];
	}

	template <typename T = char>
	Array2D<T>::~Array2D() {
		delete[] m_data;
	}

	template <typename T = char>
	void Array2D<T>::clear(const T & value) {
		for (uint32_t i = 0; i < NR*NC; i++) {
			m_data[i] = value;
		}
	}
}