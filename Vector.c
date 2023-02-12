/**
 * Test suite for Vector.h
 */

#include "Vector.h"

#include <assert.h>

DEFINE_VECTOR_TYPE(int, Vec);

void new_works(void) {
	Vec *v = Vec_new(11);

	assert(v->capacity == 11);
	assert(v->size == 0);
	assert(v->data != NULL);

	Vec_free(v);
}

void iterators_work(void) {
	Vec *v = Vec_new(99);

	assert(Vec_begin(v) == v->data);
	assert(Vec_end(v) == (v->data + v->size));

	Vec_free(v);
}

void accessors_mutators_work(void) {
	Vec *v = Vec_new(0);
	for (int i = 0; i < 3; ++i) {
		Vec_insert(v, v->size, i + 1);
	}

	assert(Vec_at(v, 0) == 1);
	assert(Vec_at(v, 1) == 2);
	assert(Vec_at(v, 2) == 3);

	Vec_remove(v, 0);

	assert(Vec_at(v, 0) == 2);
	assert(Vec_at(v, 1) == 3);

	Vec_free(v);
}

void push_pop_work(void) {
	Vec *v = Vec_new(0);

	Vec_push(v, 1);
	Vec_push(v, 2);
	Vec_push(v, 3);

	assert(Vec_pop(v) == 3);
	assert(Vec_pop(v) == 2);
	assert(Vec_pop(v) == 1);

	Vec_free(v);
}

void resize_works(void) {
	Vec *v = Vec_new(0);

	Vec_push(v, 1);
	Vec_push(v, 2);
	Vec_push(v, 3);

	Vec_resize(v, 1);

	assert(v->capacity == 1);
	assert(v->size == 1);
	assert(Vec_pop(v) == 1);

	Vec_free(v);

	v = Vec_new(0);

	Vec_push(v, 1);
	Vec_push(v, 2);
	Vec_push(v, 3);

	Vec_resize(v, 0);

	assert(v->capacity == 0);
	assert(v->size == 0);
	assert(v->data == NULL);

	Vec_free(v);
}

int main(void) {
	new_works();
	iterators_work();
	accessors_mutators_work();
	push_pop_work();
	resize_works();
}
