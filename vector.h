#include <stddef.h>

/*
  A zero-based indexed dynamic array for ints.
 */
typedef struct IntVec IntVec;
struct IntVec {
	int* data;
	size_t limit;
	size_t current; // 1 greater than the index of the last pushed item

	void (*push)(IntVec* self, int item);
	int (*pop)(IntVec* self);
	int (*nth)(IntVec* self, int n);
	void (*ins)(IntVec* self, int index, int item);
	void (*del)(IntVec* self, int index);
};


IntVec* new_int_vec(size_t limit);

void double_limit(IntVec* self);

void int_vec_push(IntVec* self, int item);
void int_vec_insert(IntVec* self, int index, int item);
void int_vec_delete(IntVec* self, int index);
int int_vec_pop(IntVec* self);
int int_vec_nth(IntVec* self, int n);

void destroy_int_vec(IntVec* self);

#define _call(N, F, ...) N->F(N, ##__VA_ARGS__)
