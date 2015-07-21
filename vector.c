#include <stddef.h>
#include <stdlib.h>
#include "vector.h"
#include "dbg.h"

IntVec* new_int_vec(size_t limit)
{
	IntVec* proto = malloc(sizeof(IntVec));
	check_mem(proto);

	int* intptr = malloc(sizeof(int) * limit);
	check_mem(intptr);

	return init_int_vec(proto, intptr, limit);

error:
	return NULL;
}

IntVec* init_int_vec(IntVec* proto, int* intptr, size_t limit)
{
	proto->data = intptr;
	proto->limit = limit;
	proto->current = 0;

	proto->pop = &int_vec_pop;
	proto->push = &int_vec_push;
	proto->nth = &int_vec_nth;
	proto->ins = &int_vec_insert;
	proto->del = &int_vec_delete;

	return proto;
}

void int_vec_double_limit(IntVec* self)
{
	int* old_data = realloc(self->data, sizeof(int) * self->limit * 2);
	check_mem(old_data);
	self->data = old_data;
	self->limit *= 2;

	return;

error:
	log_err("Could not double the capacity of a vector!");
}

void int_vec_push(IntVec* self, int item)
{
	if (self->current > self->limit) {
		log_err("Could not push item onto vector! current is greater than limit.");
		return;
	} else if (self->current == self->limit) {
		int_vec_double_limit(self);
	}

	self->data[self->current++] = item;
}

int int_vec_pop(IntVec* self)
{
	check(self->current != 0, "Tried to pop when there weren't any items.");
	return self->data[--self->current];

error:
	return 0;
}

int int_vec_nth(IntVec* self, int n)
{
	check((size_t)n < self->current,
		  "Tried to get the value of an item at an index greater than current!");

	return self->data[n];

error:
	return 0;
}

// index is the index that you want item to be at.
void int_vec_insert(IntVec* self, int index, int item)
{
	check((size_t)index <= self->current,
		  "Cannot insert item at index greater than current!");

	if ((size_t)self->current == self->limit)
		int_vec_double_limit(self);

	for (size_t i = self->current; i > (size_t)index; i--)
		self->data[i] = self->data[i - 1];

	self->data[index] = item;
	self->current++;

error:
	return;
}

void int_vec_delete(IntVec* self, int index)
{
	check((size_t)index <= self->current,
		"Cannot delete item at index greater than current!");

	for (size_t i = index; i < self->current; i++) {
		self->data[i] = self->data[i + 1];
	}

	self->current--;

error:
	return;
}

void destroy_int_vec(IntVec* self)
{
	free(self->data);
	free(self);
}
