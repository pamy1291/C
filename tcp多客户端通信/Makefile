CC=gcc
STD=-std=gnu99
FLAG=-Wall -Werror
BIN=chatS chatC
LIB=-lnetwork -lthreadpool -ldouble_list -pthread
TOOLS=tools.c

.PHONY:all
all:$(BIN)
	./chatS 127.0.0.1 6668
		
%:%.c
	$(CC) $(STD) $(FLAG) $(TOOLS) $< $(LIB) -o $@

.PHONY:clean	
clean:
	rm -rf $(BIN)
	rm -rf *.h.gch *~
