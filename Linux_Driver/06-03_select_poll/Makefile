CFILES = hello.c

obj-m += sample.o
sample-objs := $(CFILES:.c=.o)

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc simple_read.c -o simple_read
	gcc non_blocking_read.c -o non_blocking_read
	gcc select_read.c -o select_read
	gcc poll_read.c -o poll_read

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f myprog

