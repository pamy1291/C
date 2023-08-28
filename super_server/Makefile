CC=gcc
BIN=bms.bin
OBJ=super_test.o public.o superoper.o
FLAG=-Wall -Werror

all:$(OBJ)
	$(CC) $(OBJ) -o $(BIN)

%.o:%.c
	#$(CC) -c $(FLAG) $< -o $@
	$(CC) -c $< -o $@
	#gcc -c -Wall main.c -o main.o
	
clean:
	rm -rf $(BIN) $(OBJ)
	
