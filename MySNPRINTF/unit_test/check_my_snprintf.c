#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include "check_my_snprintf.h"
#include "my_snprintf.h"
#include <string.h>
#include <stdio.h>


START_TEST(test_my_snprintf_without_spec)
{
    char data[12];
    char test[12];
    int data_size, test_size;

    data_size = my_snprintf(data, sizeof(data), "Hello World");

    test_size = snprintf(test, sizeof(test), "Hello World");
    ck_assert_str_eq(data, test);
    ck_assert_int_eq(test_size, data_size);
}
END_TEST

// только спецификатор s
START_TEST(test_my_snprintf_only_s_spec)
{
    char data[12];
    char test[12];
    char data1[] = "Hello World";
    int data_size, test_size;

    data_size = my_snprintf(data, sizeof(data), "%s", data1);
    test_size = snprintf(test, sizeof(test), "%s", data1);

    ck_assert_str_eq(data, test);
    ck_assert_int_eq(test_size, data_size);
}
END_TEST

// строка и спецификатор s
START_TEST(test_my_snprintf_str_and_s_spec)
{
    char data[12];
    char data1[] = "World";
    char test[] = "Hello World";
    int test_size = strlen(test);
    int data_size;

    data_size = my_snprintf(data, sizeof(data), "Hello %s", data1);
    test_size = snprintf(test, sizeof(test), "Hello %s", data1);

    ck_assert_str_eq(data, test);
    ck_assert_int_eq(test_size, data_size);
}
END_TEST

// только спецификатор s (несколько строк)
START_TEST(test_my_snprintf_some_s_spec)
{
    char data[12], test[12];
    char data1[] = "Hello";
    char data2[] = "World";
    int data_size, test_size;
    data_size = my_snprintf(data, sizeof(data), "%s %s", data1, data2);
    test_size = snprintf(test, sizeof(data), "%s %s", data1, data2);
    ck_assert_str_eq(data, test);
    ck_assert_int_eq(data_size, test_size);
}
END_TEST

// строка и спецификатор s (несколько строк)
START_TEST(test_my_snprintf_str_and_some_s_spec)
{
    char data[16], test[16];
    char data1[] = "Hello";
    char data2[] = "World";
    int data_size, test_size;
    data_size = my_snprintf(data, sizeof(data), "aaa %s %s", data1, data2);
    test_size = snprintf(test, sizeof(test), "aaa %s %s", data1, data2);
    ck_assert_str_eq(data, test);
    ck_assert_int_eq(data_size, test_size);
}
END_TEST

// только спецификатор x
START_TEST(test_my_snprintf_only_x_spec)
{
    char data[3];
    int data1 = 16;
    char test[3];
    int test_size = snprintf(test, 3, "%x", data1);
    int data_size;
    data_size = my_snprintf(data, sizeof(data), "%x", data1);
    ck_assert_str_eq(data, test);
    ck_assert_int_eq(data_size, test_size);
}
END_TEST

// строка и спецификатор x
START_TEST(test_my_snprintf_str_and_x_spec)
{
    char data[16];
    char test[16];
    int data1 = 16;
    int data_size, test_size;
    data_size = my_snprintf(data, sizeof(data), "16 in hex is %x", data1);
    test_size = snprintf(test, sizeof(test), "16 in hex is %x", data1);
    ck_assert_str_eq(data, test);
    ck_assert_int_eq(data_size, test_size);
}
END_TEST

// токлько спецификатор x (несколько чисел)
START_TEST(test_my_snprintf_some_x_spec)
{
    char data[5];
    int data1 = 16;
    int data2 = 10;
    char test[] = "10 a";
    int test_size = snprintf(NULL, 0, "%x %x", data1, data2);
    int data_size;
    data_size = my_snprintf(data, sizeof(data), "%x %x", data1, data2);
    ck_assert_str_eq(data, test);
    ck_assert_int_eq(data_size, test_size);
}
END_TEST

// строка и спецификатор x (несколько чисел)
START_TEST(test_my_snprintf_str_and_some_x_spec)
{
    char data[32];
    int data1 = 16;
    int data2 = 10;
    char test[] = "16 in hex is 10, 10 in hex is a";
    int test_size = snprintf(NULL, 0, "16 in hex is %x, 10 in hex is %x", data1, data2);
    int data_size;
    data_size = my_snprintf(data, sizeof(data), "16 in hex is %x, 10 in hex is %x", data1, data2);
    ck_assert_str_eq(data, test);
    ck_assert_int_eq(data_size, test_size);
}
END_TEST

// только спецификаторы 
START_TEST(test_my_snprintf_only_specs)
{
    char data[15], test[15];
    char data1[] = "10 in hex is";
    int data2 = 10;
    int data_size, test_size;
    test_size = snprintf(test, sizeof(test), "%s %x", data1, data2);
    data_size = my_snprintf(data, sizeof(data), "%s %x", data1, data2);
    ck_assert_str_eq(data, test);
    ck_assert_int_eq(data_size, test_size);
}
END_TEST

// несколько спецификаторов 
START_TEST(test_my_snprintf_some_specs)
{
    char data[32], test[32];
    char data1[] = "10 in hex is";
    int data2 = 10;
    char data3[] = "16 in hex is";
    int data4 = 16;
    int data_size, test_size;
    data_size = my_snprintf(data, sizeof(data), "%s %x, %s %x", data1, data2, data3, data4);
    test_size = snprintf(test, sizeof(test), "%s %x, %s %x", data1, data2, data3, data4);
    ck_assert_str_eq(data, test);
    ck_assert_int_eq(data_size, test_size);
}

// вместо буфера - NULL 
START_TEST(test_my_snprintf_NULL_buf)
{
    char *data = NULL;
    char data1[] = "10 in hex is";
    int test = strlen(data1);
    int cnt;

    // Здесь не нужно сравнивать строки, поскольку буфер равен NULL
    cnt = my_snprintf(data, 0, "%s", data1);
    ck_assert_int_eq(cnt, test);
}
END_TEST

// слишком маленький буфер 
START_TEST(test_my_snprintf_too_small_buffer)
{
    char data[4];
    char data1[] = "10 in hex is";
    int data2 = 10;
    char data3[] = "16 in hex is";
    int data4 = 16;
    int data_size, test_size;
    data_size = my_snprintf(data, sizeof(data), "%s %x, %s %x", data1, data2, data3, data4);
    test_size = 31;
    ck_assert_int_eq(data_size, test_size);
}

Suite* my_snprintf_suite(void)
{
	Suite *s;
	TCase *tc_pos;

	s = suite_create("my_snprintf\n");

	tc_pos = tcase_create("pos:");

	tcase_add_test(tc_pos, test_my_snprintf_without_spec);
	tcase_add_test(tc_pos, test_my_snprintf_only_s_spec);
	tcase_add_test(tc_pos, test_my_snprintf_str_and_s_spec);
	tcase_add_test(tc_pos, test_my_snprintf_some_s_spec);
	tcase_add_test(tc_pos, test_my_snprintf_str_and_some_s_spec);
	tcase_add_test(tc_pos, test_my_snprintf_only_x_spec);
	tcase_add_test(tc_pos, test_my_snprintf_str_and_x_spec);
	tcase_add_test(tc_pos, test_my_snprintf_some_x_spec);
	tcase_add_test(tc_pos, test_my_snprintf_str_and_some_x_spec);
	tcase_add_test(tc_pos, test_my_snprintf_only_specs);
	tcase_add_test(tc_pos, test_my_snprintf_some_specs);
	tcase_add_test(tc_pos, test_my_snprintf_NULL_buf);
	tcase_add_test(tc_pos, test_my_snprintf_too_small_buffer);

	suite_add_tcase(s, tc_pos);

	return s;
}