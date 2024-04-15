#include <check.h>

#include "check_my_snprintf.h"
#include "check_main.h"

int main(void)
{
	SRunner *sr;
	int no_falures = 0;
	
	sr = srunner_create(my_snprintf_suite());

	srunner_run_all(sr, CK_NORMAL);
	
	no_falures = srunner_ntests_failed(sr);
	
	srunner_free(sr);
	
   	return (no_falures == 0) ? 0 : 1;
}
  