#pragma once
#include <stdint.h>
#include <stdlib.h>

namespace MFWAlg {
	template <typename T=char>
		class Array2D {
			private:
				uint32_t NR;// 行数
				uint32_t NC;// 列数
				T * m_data;// 数据
			public:
				Array2D(uint32_t nrow, uint32_t ncol);
				~Array2D();
			private:
				Array2D(const Array2D&);	
				Array2D& operator=(const Array2D&);	
		public:
				inline const uint32_t row() const { return NR; }
				inline const uint32_t col() const { return NC; }
				inline T& operator() (int row, int col) { return this->m_data[row*NC + col]; }
				const inline T& operator() (int row, int col) const { return this->m_data[row*NC + col]; }
				inline T* operator[] (int row) { return &(m_data[row * NC]); }
				inline const T* operator[] (int row) const { return &(m_data[row * NC]); }
				void clear(const T & value);
		};
}
