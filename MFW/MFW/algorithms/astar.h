#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "heap.h"
#include "hash_table.h"
#include "2darray.h"

namespace MFWAlg {
	class AStar {
		public:
			/**
			 * A-Star algorithm result;
			 */
			struct AStarResult {
				int * path; // the path format:
				// [X1Y1X2Y2X3Y3.....XnYnX1Y1] 
				// interleaving X,Y coordinate
				int num_nodes;
				~AStarResult() 
				{
					delete [] path;
					path = NULL;
				}
			};
			static const unsigned char WALL = 0xFF;
		private:
			const Array2D<unsigned char> & m_grid;	
			// the openset
			Heap<uint32_t> m_openset;
			// The set of nodes open -- for fast testing of a point in openset. heap contains test is quite slow -- O(n)
			Array2D<bool> m_openset_grid;
			// The set of nodes already evaluated.
			Array2D<bool> m_closedset;
			// Cost from start along best known path.	
			Array2D<float> g_score;
			// Estimated total cost from start to goal through y.
			Array2D<float> f_score;
		public:
			AStar(const Array2D<unsigned char> & grid);

			/**
			 * the A* algorithm
			 * search a path from (x1,y1) to (x2,y2)
			 * a integer representing path is returned, you should delete it after. 
			 */
			AStarResult * run(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
		private:
			/**
			 * Estimate the cost for going this way, such as:
			 * acrossing the swamp will be much slower than walking on the road.
			 * design for you game.
			 */
			inline float estimate(int x1, int y1, int x2, int y2) const {
				return sqrtf((x2-x1) * (x2-x1) + (y2-y1)*(y2-y1));
			}
	};

}

