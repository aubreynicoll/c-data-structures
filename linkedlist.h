/**
 * Macros that expand into a type-safe singly-linked list
 */

#ifndef __LINKEDLIST_INCLUDED__
#define __LINKEDLIST_INCLUDED__

#include <stddef.h> /* size_t */
#include <stdio.h>  /* fprintf */
#include <stdlib.h> /* malloc, free, exit */

/**
 * Declares a typedef'd linked list and defines its methods for use in the
 * current translation unit
 */
#define DEFINE_LINKEDLIST_TYPE(T, NAME)                                        \
	typedef struct NAME##_node NAME##_node;                                \
	typedef struct NAME	   NAME;                                       \
                                                                               \
	struct NAME##_node {                                                   \
		T	     value;                                            \
		NAME##_node *next;                                             \
	};                                                                     \
                                                                               \
	struct NAME {                                                          \
		size_t	     size;                                             \
		NAME##_node *head;                                             \
	};                                                                     \
                                                                               \
	static NAME##_node *NAME##_node_new(void);                             \
	static void	    NAME##_node_free(NAME##_node *this);               \
                                                                               \
	static NAME *NAME##_new(void);                                         \
	static void  NAME##_free(NAME *this);                                  \
                                                                               \
	static T    NAME##_at(NAME *this, size_t index);                       \
	static void NAME##_insert(NAME *this, size_t index, T value);          \
	static void NAME##_remove(NAME *this, size_t index);                   \
                                                                               \
	static NAME##_node *NAME##_node_new(void) {                            \
		NAME##_node *node = malloc(sizeof(NAME##_node));               \
		if (!node) {                                                   \
			fprintf(stderr, #NAME "_node_new(): out of memory\n"); \
			exit(EXIT_FAILURE);                                    \
		}                                                              \
		return node;                                                   \
	}                                                                      \
                                                                               \
	static void NAME##_node_free(NAME##_node *this) { free(this); }        \
                                                                               \
	static NAME *NAME##_new(void) {                                        \
		NAME *list = malloc(sizeof(NAME));                             \
		if (!list) {                                                   \
			fprintf(stderr, #NAME "_new(): out of memory\n");      \
			exit(EXIT_FAILURE);                                    \
		}                                                              \
		*list = (NAME){};                                              \
		return list;                                                   \
	}                                                                      \
                                                                               \
	static void NAME##_free(NAME *this) {                                  \
		NAME##_node *curr = this->head, *prev = NULL;                  \
		while (curr) {                                                 \
			prev = curr;                                           \
			curr = curr->next;                                     \
			NAME##_node_free(prev);                                \
		}                                                              \
		free(this);                                                    \
	}                                                                      \
                                                                               \
	static T NAME##_at(NAME *this, size_t index) {                         \
		if (index >= this->size) {                                     \
			fprintf(stderr,                                        \
				#NAME "_at(): out of bounds access\n");        \
			exit(EXIT_FAILURE);                                    \
		}                                                              \
		NAME##_node *curr = this->head;                                \
		while (index--) {                                              \
			curr = curr->next;                                     \
		}                                                              \
		return curr->value;                                            \
	}                                                                      \
                                                                               \
	static void NAME##_insert(NAME *this, size_t index, T value) {         \
		if (index > this->size) {                                      \
			fprintf(stderr,                                        \
				#NAME "_insert(): out of bounds insertion\n"); \
			exit(EXIT_FAILURE);                                    \
		}                                                              \
		if (index) {                                                   \
			NAME##_node *curr = this->head, *prev = NULL;          \
			while (index--) {                                      \
				prev = curr;                                   \
				curr = curr->next;                             \
			}                                                      \
			NAME##_node *new_node = NAME##_node_new();             \
			*new_node =                                            \
			    (NAME##_node){.value = value, .next = curr};       \
			prev->next = new_node;                                 \
		} else {                                                       \
			NAME##_node *new_node = NAME##_node_new();             \
			*new_node =                                            \
			    (NAME##_node){.value = value, .next = this->head}; \
			this->head = new_node;                                 \
		}                                                              \
		++this->size;                                                  \
	}                                                                      \
                                                                               \
	static void NAME##_remove(NAME *this, size_t index) {                  \
		if (index >= this->size) {                                     \
			fprintf(stderr,                                        \
				#NAME "_remove(): out of bounds removal\n");   \
			exit(EXIT_FAILURE);                                    \
		}                                                              \
		if (index) {                                                   \
			NAME##_node *curr = this->head, *prev = NULL;          \
			while (index--) {                                      \
				prev = curr;                                   \
				curr = curr->next;                             \
			}                                                      \
			prev->next = curr->next;                               \
			NAME##_node_free(curr);                                \
		} else {                                                       \
			NAME##_node *curr = this->head;                        \
			this->head = curr->next;                               \
			NAME##_node_free(curr);                                \
		}                                                              \
		--this->size;                                                  \
	}

#endif
