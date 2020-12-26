CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: hatterspeak

hatterspeak: hatterspeak.o
	$(CC) -o hatterspeak hatterspeak.o -lm

hatterspeak.o: hatterspeak.c
	$(CC) $(CFLAGS) -c hatterspeak.c



valgrind:
	valgrind ./hatterspeak

clean:
	rm -f hatterspeak hatterspeak.o  userinputs.txt hatterkeys.txt

infer:
	make clean; infer-capture -- make; infer-analyze -- make

format:
	clang-format -i -style=file *.c *.h