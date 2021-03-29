CFILES = hello.c

obj-m := sample.o
sample-objs := $(CFILES:.c=.o)

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc simple.c -o myprog

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f myprog

