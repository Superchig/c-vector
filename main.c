#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "dbg.h"

void test_push();
void test_pop();


int main()
{
	test_push();
	printf("\n\n\n");
	test_pop();
}

void test_push()
{
	puts("Creating vec.");
	IntVec* vec = new_int_vec(2);

	puts("\nPushing 7 onto vec.");

	int_vec_push(vec, 7);
	printf("current: %lu\n", vec->current);
	printf("vec[0]: %d\n", int_vec_nth(vec, 0));

	puts("\nPushing 42 onto vec.");

	int_vec_push(vec, 42);
	printf("current: %lu\n", vec->current);
	printf("vec[1]: %d\n", int_vec_nth(vec, 1));

	printf("vec->limit: %lu\n", vec->limit);

	puts("\nPushing 8 onto vec.");

	int_vec_push(vec, 8);
	printf("current: %lu\n", vec->current);
	printf("vec->limit: %lu\n", vec->limit);
	printf("vec[2]: %d\n", _call(vec, nth, 2));
	printf("vec[1]: %d\n", _call(vec, nth, 1));
	printf("vec[0]: %d\n", int_vec_nth(vec, 0));

	destroy_int_vec(vec);
}

void test_pop()
{
	puts("Creating vec.");
	IntVec* vec = new_int_vec(2);

	int_vec_push(vec, 7);
	int_vec_push(vec, 14);
	int_vec_push(vec, 21);

	printf("current: %lu\n", vec->current);
	printf("popping vec: %d\n", _call(vec, pop));
	printf("current: %lu\n", vec->current);

	vec->pop(vec);
	vec->pop(vec);

	vec->pop(vec);

	destroy_int_vec(vec);
}
