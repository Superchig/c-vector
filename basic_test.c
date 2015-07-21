#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "vector.h"

static void push_test(void **state)
{
	IntVec* vec = new_int_vec(2);

	_call(vec, push, 7);
	_call(vec, push, 42);
	_call(vec, push, 8);

	assert_int_equal(7, _call(vec, nth, 0));
	assert_int_equal(42, _call(vec, nth, 1));
	assert_int_equal(8, _call(vec, nth, 2));

	assert_int_equal(4, vec->limit);

	destroy_int_vec(vec);
}

static void pop_test()
{
	IntVec* vec = new_int_vec(2);

	vec->push(vec, 7);
	vec->push(vec, 42);
	vec->push(vec, 8);

	assert_int_equal(8, vec->pop(vec));
	assert_int_equal(42, vec->pop(vec));
	assert_int_equal(7, vec->pop(vec));

	destroy_int_vec(vec);
}

static void insert_test()
{
	IntVec* vec = new_int_vec(2);

	vec->push(vec, 12);
	vec->push(vec, 42);
	vec->push(vec, 90);
	vec->push(vec, -21487);
	vec->push(vec, 789);
	vec->push(vec, 1092);
	vec->push(vec, 87);
	vec->push(vec, 7648);

	vec->ins(vec, 4, 9);

	// Test that vec->limit is doubled by vec->ins when it is reached.
	assert_int_equal(16, vec->limit);

	// Test that inserted value is in the right area.
	assert_int_equal(9, vec->nth(vec, 4));

	// Test that the following values have been moved up successfully.
	assert_int_equal(789, vec->nth(vec, 5));
	assert_int_equal(1092, vec->nth(vec, 6));
	assert_int_equal(87, vec->nth(vec, 7));
	assert_int_equal(7648, vec->nth(vec, 8));

	destroy_int_vec(vec);
}

static void delete_test()
{
	IntVec* vec = new_int_vec(2);

	vec->push(vec, 7);
	vec->push(vec, 91);
	vec->push(vec, 561);
	vec->push(vec, 78);
	vec->push(vec, 57);

	vec->del(vec, 1);
	printf("current: %lu", vec->current);

	printf("[ ");
	for (size_t i = 0; i < vec->current; i++)
	{
		printf("%d ", vec->nth(vec, i));
	}
	printf("]\n");

	assert_int_equal(561, vec->nth(vec, 1));
	assert_int_equal(4, vec->current);

	destroy_int_vec(vec);
}

int main()
{
	const struct CMUnitTest test[] = {
		cmocka_unit_test(push_test),
		cmocka_unit_test(pop_test),
		cmocka_unit_test(insert_test),
		cmocka_unit_test(delete_test),
	};

	printf("\n-------\n");

	return cmocka_run_group_tests(test, NULL, NULL);
}
