#include "check_array_func.h"

#include <stddef.h>
#include <stdbool.h>
#define OK 0
#define ERR_MEM 1

//сравнивает два массива целых чисел
static bool array_cmp(const int *a, const int *b, size_t size1, size_t size2)
{
	if (size1 != size2)
	{
		return false;
	}
	for (size_t i = 0; i < size1; i++)
	{
        if (a[i]!= b[i])
		{
            return false;
        }
    }
    return true;
}

START_TEST(test_fill_in_the_numbers_fibonacci_valid_input)
{
    int array[10];
    int expected[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34};
    int result = fill_in_the_numbers_fibonacci(array, 10);

    ck_assert_int_eq(result, OK);

    ck_assert_int_eq(true, array_cmp(array, expected, 10, 10));
}
END_TEST

START_TEST(test_fill_in_the_numbers_fibonacci_invalid_input)
{
    int array[5];
    int result = fill_in_the_numbers_fibonacci(array, 0);

    ck_assert_int_eq(result, ERR_CNT);
}
END_TEST

START_TEST(test_fill_in_the_numbers_fibonacci_small_input)
{
    int array[2];
	int expected[] = {0, 1};
    int result = fill_in_the_numbers_fibonacci(array, 2);

    ck_assert_int_eq(result, OK);
	ck_assert_int_eq(true, array_cmp(array, expected, 2, 2));
}
END_TEST

Suite* fill_in_the_numbers_fibonacci_suite(void)
{
	Suite *s;
	TCase *tc_pos;

	s = suite_create("fill_in_the_numbers_fibonacci\n");

 	tc_pos = tcase_create("pos:");
    tcase_add_test(tc_pos, test_fill_in_the_numbers_fibonacci_valid_input);
    tcase_add_test(tc_pos, test_fill_in_the_numbers_fibonacci_invalid_input);
    tcase_add_test(tc_pos, test_fill_in_the_numbers_fibonacci_small_input);

	suite_add_tcase(s, tc_pos);

	return s;
}

START_TEST(test_get_the_first_entry_of_elements_valid_input)
{
    int input[] = {1, 2, 3, 4, 3, 1, 2, 3};
    int input_cnt = 8;
    int output[4];
    int output_cnt;
    int mode = 1;

    int result = get_the_first_entry_of_elements(input, input_cnt, output, &output_cnt, mode);

    // Проверка, что функция вернула OK
    ck_assert_int_eq(result, OK);

    // Проверка корректности полученного массива без дубликатов
    int expected[] = {1, 2, 3, 4};
    ck_assert_int_eq(output_cnt, 4);
    for (int i = 0; i < output_cnt; i++)
    {
        ck_assert_int_eq(output[i], expected[i]);
    }
}
END_TEST

START_TEST(test_get_the_first_entry_of_elements_no_duplicates)
{
    int input[] = {1, 2, 3, 4, 5};
    int input_cnt = 5;
    int output[5];
    int output_cnt;
    int mode = 1;

    int result = get_the_first_entry_of_elements(input, input_cnt, output, &output_cnt, mode);

    // Проверка, что функция вернула OK
    ck_assert_int_eq(result, OK);

    // Проверка, что полученный массив равен входному, так как нет дубликатов
    ck_assert_int_eq(output_cnt, input_cnt);
    for (int i = 0; i < input_cnt; i++)
    {
        ck_assert_int_eq(output[i], input[i]);
    }
}
END_TEST

START_TEST(test_get_the_first_entry_of_elements_empty_input)
{
    int input[] = {};
    int input_cnt = 0;
    int output[10];
    int output_cnt;
    int mode = 1;

    int result = get_the_first_entry_of_elements(input, input_cnt, output, &output_cnt, mode);

    // Проверка, что функция вернула ERR_CNT для пустого входного массива
    ck_assert_int_eq(result, ERR_CNT);
}
END_TEST

Suite* get_the_first_entry_of_elements_suite(void)
{
	Suite *s;
	TCase *tc_pos;

	s = suite_create("get_the_first_entry_of_elements\n");

	tc_pos = tcase_create("pos:");

    tcase_add_test(tc_pos, test_get_the_first_entry_of_elements_valid_input);
    tcase_add_test(tc_pos, test_get_the_first_entry_of_elements_no_duplicates);
    tcase_add_test(tc_pos, test_get_the_first_entry_of_elements_empty_input);


	suite_add_tcase(s, tc_pos);

	return s;
}




