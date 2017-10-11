#pragma once

#include <vector>

#define LSONE(x) (x & (-x))

class Fenwick
{
	private:
		// Vector representing the table
		std::vector<int> fen;
	public:
		Fenwick() {}

		// We don't use the index 0, because it is the base case
		Fenwick(int n)
		{
			fen.assign(n + 1, 0);
		}

		// Calculate the 
		int rsq(int a)
		{
			int ans = 0;
			for(; a; a -= LSONE(a))
				ans += fen[a];
			return ans;
		}

		// RSQ a..b
		inline int rsq(int a, int b)
		{
			return rsq(b) - (a == 1 ? 0 : rsq(a - 1));
		}

		// Update the value of the k-th element by x
		void update(int k, int x)
		{
			for(; k < (int)fen.size(); k += LSONE(k))
				fen[k] += x;	
		}
};


