#pragma once

namespace MFWAlg {
	template<typename T>
		struct Set{
			Set<T>* parent;
			int rank;
		};

	template<typename T>
		void MakeSet(T *s){
			s->parent = s;
			s->rank = 0;
		}

	template<typename T>
		void Union(T *x, T *y) {
			Link(FindSet(x), FindSet(y));
		}

	template<typename T>
		void Link(T *x, T *y) {
			if (x->rank > y->rank) {
				y->parent = x;
			} else {
				x->parent = y;
				if (x->rank == y->rank) {
					y->rank +=1;
				}
			}
		}

	template<typename T>
		T* FindSet(T *x) {
			if (x != x->parent) {
				x->parent = FindSet(x->parent);
			}

			return x->parent;
		}
}

