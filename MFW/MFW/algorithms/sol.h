#pragma once
#include "double_linked_list.h"

namespace MFWAlg {
	/**
	 * Move a node to the front
	 */
	static inline void list_mtf(struct list_head *entry, struct list_head *head) {
		if (entry->prev == head) return;
		list_del_(entry->prev, entry->next);
		list_add_(entry, head, head->next);
	}


	/**
	 * Move a node ahead one position
	 */
	static inline void list_mao(struct list_head *entry, struct list_head * head) {
		// if the entry in the 1st position
		if (entry->prev == head) return;
		struct list_head * prev = entry->prev;
		list_del_(entry->prev, entry->next);
		list_add_(entry, prev->prev, prev);
	}
}
