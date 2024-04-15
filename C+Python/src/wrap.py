import ctypes

array_lib = ctypes.CDLL('./lib/libarray_func.so')
#int fill_in_the_numbers_fibonacci(int *array, int cnt)
_fill_in_the_numbers_fibonacci = array_lib.fill_in_the_numbers_fibonacci
_fill_in_the_numbers_fibonacci.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int)
_fill_in_the_numbers_fibonacci.restype = ctypes.c_int

def fill_in_the_numbers_fibonacci(src_len):
    src = (ctypes.c_int * src_len)()
    rc = _fill_in_the_numbers_fibonacci(src, src_len)
    return rc, list(src)

#int get_the_first_entry_of_elements(int *input, int input_cnt, int *output, int *output_cnt, int mode);

_get_the_first_entry_of_elements = array_lib.get_the_first_entry_of_elements
_get_the_first_entry_of_elements.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int), ctypes.c_int)
_get_the_first_entry_of_elements.restype = ctypes.c_int

def get_the_first_entry_of_elements(input_nums, mode):
    src_len = len(input_nums)
    src = (ctypes.c_int * src_len)(*input_nums)
    dst_len = ctypes.c_int(0)
    
    if mode == 1:
        dst = (ctypes.c_int * src_len)()
        rc = _get_the_first_entry_of_elements(src, src_len, dst, dst_len, 1)
    else:
        rc = _get_the_first_entry_of_elements(src, src_len, None, dst_len, 0)
        if rc == 0:
            dst = (ctypes.c_int * dst_len.value)()
            rc = _get_the_first_entry_of_elements(src, src_len, dst, dst_len, 1)
    
    if rc == 0:
        return rc, list(dst[:dst_len.value])  # Convert only the valid elements to a list
    else:
        return rc, list()
