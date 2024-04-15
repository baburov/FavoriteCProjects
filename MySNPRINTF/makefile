


CC := gcc
CFLAGS := -std=c99 -Wall -Wpedantic -Werror -I./inc 
DBGFLAGS := -g 
COVERAGEFLAGS := -coverage
ASANFLAGS := -fno-omit-frame-pointer -g -fsanitize=address
MSANFLAGS := -fno-omit-frame-pointer -g -fsanitize=memory
UBSANFLAGS := -fno-omit-frame-pointer -g -fsanitize=undefined

SRC_DIR := ./src/
INC_DIR := ./inc/
OBJ_DIR := ./out/
UNIT_DIR := ./unit_test/

OBJ := $(OBJ_DIR)my_snprintf.o
UNIT_OBJ := $(UNIT_DIR)check_my_snprintf.o $(UNIT_DIR)check_main.o $(OBJ)
.PHONY: clean debug coverage asan msan ubsan unit v clean_unit u

debug: CFLAGS += $(DBGFLAGS)
debug: app.exe

coverage: CFLAGS += $(COVERAGEFLAGS)
coverage: app.exe

asan: CC = clang
asan: CFLAGS += $(ASANFLAGS)
asan: app.exe

msan: CC = clang
msan: CFLAGS += $(MSANFLAGS)
msan: app.exe

ubsan: CC = clang
ubsan: CFLAGS += $(UBSANFLAGS)
ubsan: app.exe

app.exe: $(OBJ) $(OBJ_DIR)main.o
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@ 

unit: unit_tests.exe
unit_tests.exe: $(UNIT_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -lcheck -lm #-lsubunit
$(UNIT_DIR)%.o: $(UNIT_DIR)%.c
	mkdir -p $(UNIT_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@ 
	
# $(UNIT_DIR)check_main.o: $(UNIT_DIR)check_main.c $(INC_DIR)check_matrix_math.h $(INC_DIR)check_matrix_gauss.h	
# 	$(CC) $(CFLAGS) -c $< -o $@
# $(UNIT_DIR)check_matrix_math.o: $(UNIT_DIR)check_matrix_math.c $(INC_DIR)check_matrix_math.h
# 	$(CC) $(CFLAGS) -c $< -o $@
# $(UNIT_DIR)check_matrix_gauss.o: $(UNIT_DIR)check_matrix_gauss.c $(INC_DIR)check_matrix_gauss.h
# 	$(CC) $(CFLAGS) -c $< -o $@


	

func:
	bash sanitize_tests.sh
v:
	make -s valgrind
valgrind:
	bash sanitize_tests.sh valgrind
u:
	make -s unit
unit:
	valgrind --quiet --leak-check=yes --track-origins=yes ./unit_tests.exe && make clean_unit
clean:
	rm -r ./out *.exe
clean_unit:
	rm -r ./out *.exe ./unit_test/*.o
