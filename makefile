CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -std=c99 -pedantic
DEPS = qsexterno.h
Vflags = valgrind --leak-check=full
OBJ = main.o qsexterno.o funcoes_auxiliares.o
%.o: %.c $(DEPS)
				$(CC) -c -o $@ $< $(CFLAGS)

exec: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

	rm -rf *.o

run: exec
	./exec

val: exec
	$(Vflags) ./exec

testes: exec
	$(Vflags) ./exec < toy_0_input 
	$(Vflags) ./exec < toy_1_input
	$(Vflags) ./exec < toy_2_input
	$(Vflags) ./exec < toy_3_input
	$(Vflags) ./exec < toy_4_input
	$(Vflags) ./exec < toy_5_input
	$(Vflags) ./exec < toy_6_input
	$(Vflags) ./exec < toy_7_input
	$(Vflags) ./exec < toy_8_input
	$(Vflags) ./exec < toy_9_input
