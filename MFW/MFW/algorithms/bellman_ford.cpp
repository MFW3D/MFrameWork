#include "bellman_ford.h"

namespace MFWAlg {
	BellmanFord::BellmanFord(const Graph & graph) :
		dist(graph.vertex_count()), g(graph) { }
	HashTable<int32_t, int32_t> * BellmanFord::run(uint32_t source) {
		// hash table for previous vertex
		HashTable<int32_t, int32_t> *  previous = new HashTable<int32_t, int32_t>(g.vertex_count());
		// source vertex
		dist[source] = 0;

		// other vertices
		Graph::Adjacent * a;
		list_for_each_entry(a, &g.list(), a_node) {
			if (source != a->v.id) {
				dist[a->v.id] = INT_MAX;
			}
			(*previous)[a->v.id] = UNDEFINED;
		}

		has_neg_cycle = false;	// negative cycle mark set to 'false'.

								//  relax edges repeatedly	
		Graph::Adjacent * u;
		for (uint32_t i = 0; i < g.vertex_count() - 1; i++) {    // loop |V| -1 times
			list_for_each_entry(u, &g.list(), a_node) { // for each eage(u,v) in edges
				int32_t dist_u = dist[u->v.id];

				Graph::Vertex * v;
				list_for_each_entry(v, &u->v_head, v_node) {
					int32_t dist_v = dist[v->id];

					if (dist_u + v->weight < dist_v) {
						dist[v->id] = dist_u + v->weight;
						(*previous)[v->id] = u->v.id;
					}
				}
			}
		}

		//  check for negative-weight cycles
		list_for_each_entry(u, &g.list(), a_node) {
			int32_t dist_u = dist[u->v.id];

			Graph::Vertex * v;
			list_for_each_entry(v, &u->v_head, v_node) {
				int32_t dist_v = dist[v->id];

				if (dist_u + v->weight < dist_v) {
					has_neg_cycle = true;	// graph contains a negative-weight cycle
					return previous;
				}
			}
		}

		return previous;
	}
}