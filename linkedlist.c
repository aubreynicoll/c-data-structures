#include "linkedlist.h"

#include <assert.h>

DEFINE_LINKEDLIST_TYPE(int, List);

void new_works(void) {
	List *list = List_new();

	assert(list->size == 0);
	assert(list->head == NULL);

	List_free(list);
}

void insert_at_remove_works(void) {
	List *list = List_new();

	for (int i = 0; i < 100; ++i) {
		List_insert(list, list->size, i);
	}

	assert(list->size == 100);
	assert(List_at(list, 0) == 0);
	assert(List_at(list, 42) == 42);
	assert(List_at(list, list->size - 1) == 99);

	List_insert(list, 0, -1);
	assert(list->size == 101);
	assert(List_at(list, 0) == -1);
	List_remove(list, 0);
	assert(list->size == 100);
	assert(List_at(list, 0) == 0);

	List_insert(list, 42, -1);
	assert(list->size == 101);
	assert(List_at(list, 42) == -1);
	List_remove(list, 42);
	assert(list->size == 100);
	assert(List_at(list, 42) == 42);

	List_insert(list, list->size, -1);
	assert(list->size == 101);
	assert(List_at(list, list->size - 1) == -1);
	List_remove(list, list->size - 1);
	assert(list->size == 100);
	assert(List_at(list, list->size - 1) == 99);

	List_free(list);
}

int main(void) {
	new_works();
	insert_at_remove_works();
}
