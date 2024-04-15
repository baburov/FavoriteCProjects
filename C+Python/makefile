CC := gcc
CFLAGS := -std=c99 -Wall -Werror -I./inc 
DBGFLAGS := -gcc
SRC_DIR := ./src/
INC_DIR := ./inc/
OBJ_DIR := ./out/
UNIT_DIR := ./unit_test/
LIB_DIR := ./lib/

OBJ := $(OBJ_DIR)array_func.o 
UNIT_OBJ := $(UNIT_DIR)check_array_func.o $(UNIT_DIR)check_main.o
LIBS := -lm -L$(LIB_DIR) -larray_func -lsubunit

.PHONY: clean release unit clean_unit

release: $(LIB_DIR)libarray_func.so
	python3 $(SRC_DIR)main.py

$(LIB_DIR)libarray_func.so: $(OBJ)
	mkdir -p $(LIB_DIR)
	$(CC) -shared -o $@ $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -fPIC -c $^ -o $@ 

unit: unit_tests.exe
unit_tests.exe: $(UNIT_OBJ) $(LIB_DIR)libarray_func.so
	$(CC) $(CFLAGS) $^ -o $@ -lcheck -lm -lsubunit -L$(LIB_DIR) -Wl,-rpath=$(LIB_DIR)
	
$(UNIT_DIR)check_main.o: $(UNIT_DIR)check_main.c $(INC_DIR)check_array_func.h 
	$(CC) $(CFLAGS) -c $< -o $@
$(UNIT_DIR)check_array_func.o: $(UNIT_DIR)check_array_func.c $(INC_DIR)check_array_func.h
	$(CC) $(CFLAGS) -c $< -o $@
func:
u:
	make -s unit
unit:
	valgrind --quiet --leak-check=yes ./unit_tests.exe && make clean_unit

clean:
	rm -r $(OBJ_DIR)*.o
clean_unit:
	rm -r $(UNIT_DIR)/*.o *.exe $(OBJ_DIR)*.o
