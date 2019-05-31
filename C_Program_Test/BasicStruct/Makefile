CC = gcc
CFLAGS = -g -Wall
RM = /bin/rm -f

src = $(wildcard *.c)
obj = $(src:.c=.o)

.PHONY: all
all: myprog

myprog: $(obj)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	$(RM) $(obj) myprog

run:
	./myprog
