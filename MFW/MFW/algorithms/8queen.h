#pragma once

#include <stdio.h>
#include <string.h>

namespace MFWAlg {
	class Queen8 {
		private:
			char board[8][8];
			int cnt;
		public:
			void solve();
		private:
			void _solve(int row);
			void print();
			bool check(int row, int col);
	};
}

