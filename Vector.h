/**
 * Macros that expand into a type-safe dynamically resized array
 * ADT--aka a Vector.
 */

#ifndef __VECTOR_INCLUDED__
#define __VECTOR_INCLUDED__

#include <stddef.h> /* size_t */
#include <stdio.h>  /* fprintf */
#include <stdlib.h> /* malloc, realloc, free */
#include <stdlib.h> /* exit */

/**
 * Declares a typedef'd vector and defines its methods for use in the current
 * translation unit
 */
#define DEFINE_VECTOR_TYPE(T, NAME)                                                      \
	typedef struct NAME NAME;                                                        \
	struct NAME {                                                                    \
		size_t capacity;                                                         \
		size_t size;                                                             \
		T     *data;                                                             \
	};                                                                               \
                                                                                         \
	static NAME *NAME##_new(size_t capacity);                                        \
	static void  NAME##_free(NAME *this);                                            \
                                                                                         \
	static T *NAME##_begin(NAME *this);                                              \
	static T *NAME##_end(NAME *this);                                                \
                                                                                         \
	static T    NAME##_at(NAME *this, size_t index);                                 \
	static void NAME##_insert(NAME *this, size_t index, T value);                    \
	static void NAME##_remove(NAME *this, size_t index);                             \
                                                                                         \
	static void NAME##_push(NAME *this, T value);                                    \
	static T    NAME##_pop(NAME *this);                                              \
                                                                                         \
	static void NAME##_resize(NAME *this, size_t capacity);                          \
                                                                                         \
	static NAME *NAME##_new(size_t capacity) {                                       \
		T    *data = malloc(capacity * sizeof(T));                               \
		NAME *v = malloc(sizeof(NAME));                                          \
                                                                                         \
		if (capacity && !data || !v) {                                           \
			free(data);                                                      \
			free(v);                                                         \
			return NULL;                                                     \
		}                                                                        \
                                                                                         \
		*v = (NAME){.capacity = capacity, .size = 0, .data = data};              \
		return v;                                                                \
	}                                                                                \
                                                                                         \
	static void NAME##_free(NAME *this) {                                            \
		free(this->data);                                                        \
		free(this);                                                              \
	}                                                                                \
                                                                                         \
	static T *NAME##_begin(NAME *this) { return this->data; }                        \
                                                                                         \
	static T *NAME##_end(NAME *this) { return this->data + this->size; }             \
                                                                                         \
	static T NAME##_at(NAME *this, size_t index) {                                   \
		if (index >= this->size) {                                               \
			fprintf(stderr,                                                  \
				#NAME "_at(): out of bounds vector access\n");           \
			exit(EXIT_FAILURE);                                              \
		}                                                                        \
                                                                                         \
		return this->data[index];                                                \
	}                                                                                \
                                                                                         \
	static void NAME##_insert(NAME *this, size_t index, T value) {                   \
		if (index > this->size) {                                                \
			fprintf(stderr, #NAME                                            \
				"_insert(): out of bounds vector access\n");             \
			exit(EXIT_FAILURE);                                              \
		}                                                                        \
                                                                                         \
		if (this->size == this->capacity) {                                      \
			size_t new_capacity =                                            \
			    this->capacity ? this->capacity * 2 : 1;                     \
			NAME##_resize(this, new_capacity);                               \
		}                                                                        \
                                                                                         \
		for (size_t i = this->size; i > index; --i) {                            \
			this->data[i] = this->data[i - 1];                               \
		}                                                                        \
                                                                                         \
		this->data[index] = value;                                               \
                                                                                         \
		++this->size;                                                            \
	}                                                                                \
                                                                                         \
	static void NAME##_remove(NAME *this, size_t index) {                            \
		if (index >= this->size) {                                               \
			fprintf(stderr, #NAME                                            \
				"_remove(): out of bounds vector access\n");             \
			exit(EXIT_FAILURE);                                              \
		}                                                                        \
                                                                                         \
		for (size_t i = index; i < this->size - 1; ++i) {                        \
			this->data[i] = this->data[i + 1];                               \
		}                                                                        \
                                                                                         \
		--this->size;                                                            \
	}                                                                                \
                                                                                         \
	static void NAME##_push(NAME *this, T value) {                                   \
		NAME##_insert(this, this->size, value);                                  \
	}                                                                                \
                                                                                         \
	static T NAME##_pop(NAME *this) {                                                \
		T value = NAME##_at(this, this->size - 1);                               \
		NAME##_remove(this, this->size - 1);                                     \
		return value;                                                            \
	}                                                                                \
                                                                                         \
	static void NAME##_resize(NAME *this, size_t capacity) {                         \
		if (!capacity) {                                                         \
			free(this->data);                                                \
			this->data = NULL;                                               \
		} else {                                                                 \
			this->data =                                                     \
			    realloc(this->data, capacity * sizeof(T));                   \
                                                                                         \
			if (this->data == NULL) {                                        \
				fprintf(                                                 \
				    stderr, #NAME                                        \
				    "_resize(): out of memory during resize operation"); \
				exit(EXIT_FAILURE);                                      \
			}                                                                \
		}                                                                        \
                                                                                         \
		this->capacity = capacity;                                               \
	}

#endif /* __VECTOR_INCLUDED__ */
