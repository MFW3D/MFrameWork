#include "8queen.h"
namespace MFWAlg {
	void Queen8::solve() {
		memset(board, '0', sizeof(board));
		cnt = 0;
		_solve(0);
	}
	void Queen8::_solve(int row) {	// start from 0
		int i;
		for (i = 0; i < 8; i++) {
			board[row][i] = '1';
			if (check(row, i)) {
				if (row == 7) print();
				else _solve(row + 1);
			}
			board[row][i] = '0';	// rollback
		}
	}

	void Queen8::print() {
		printf("chessboard: %d\n", ++cnt);
		int i, j;
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				printf("%c ", board[i][j]);
			}
			printf("\n");
		}
	}

	bool Queen8::check(int row, int col) {
		int i, j;

		// cannot be same column
		for (i = 0; i < row; i++) {
			if (board[i][col] == '1') {
				return false;
			}
		}

		// cannot be diagnal
		i = row - 1, j = col - 1;
		while (i >= 0 && j >= 0) {
			if (board[i][j] == '1') {
				return false;
			}
			i--;
			j--;
		}

		i = row - 1, j = col + 1;
		while (i >= 0 && j < 8) {
			if (board[i][j] == '1') {
				return false;
			}
			i--;
			j++;
		}
		return true;
	}
}