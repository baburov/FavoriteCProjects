#include <stddef.h>
#include <stdlib.h>
#include "array_func.h"

int fill_in_the_numbers_fibonacci(int *array, int cnt)
{
    if (cnt < 1)
        return ERR_CNT;

    array[0] = 0;
    if (cnt > 1)
        array[1] = 1;

    for (int i = 2; i < cnt; i++)
        array[i] = array[i - 1] + array[i - 2];

    return OK; 
}

int get_the_first_entry_of_elements(int *input, int input_cnt, int *output, int *output_cnt, int mode)
{
    if (input_cnt < 1)
        return ERR_CNT;
    int rc = OK;
    int count = 0;
    for (int i = 0; i < input_cnt; i++)
    {
        int is_duplicate = 0;

        for (int j = 0; j < i && !is_duplicate; j++)
            if (input[i] == input[j])
                is_duplicate = 1;
                
        if (!is_duplicate)
        {
            if (mode == 1)
                // Заполняем output только при mode == 1
                output[count] = input[i];
            count++;
        }
    }
    *output_cnt = count;

    return rc;
}
