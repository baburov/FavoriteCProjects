#include <check.h>

#include "check_array_func.h"
#include "check_main.h"

int main(void)
{
	SRunner *sr;
	int no_falures = 0;
	
	sr = srunner_create(fill_in_the_numbers_fibonacci_suite());
	srunner_add_suite(sr, get_the_first_entry_of_elements_suite());
	srunner_run_all(sr, CK_NORMAL);
	
	no_falures = srunner_ntests_failed(sr);
	
	srunner_free(sr);
	
   	return (no_falures == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
  
