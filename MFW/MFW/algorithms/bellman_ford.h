#pragma once
/*
�㷨�� Bellman-Ford
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>

#include "directed_graph.h"
#include "hash_table.h"

#define UNDEFINED -1

namespace MFWAlg {
	class BellmanFord {
		private:		
			HashTable<int32_t, int32_t> dist; 		// ����hash��.
			bool has_neg_cycle;						// ��Ȩ�ر��
			const Graph & g;	
		public:
			BellmanFord(const Graph & graph);
			HashTable<int32_t, int32_t> * run(uint32_t source);
			inline bool has_negative_cycle() { return has_neg_cycle; }
	};
}

