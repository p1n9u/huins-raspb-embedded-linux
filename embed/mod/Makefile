obj-m := timer_test.o

KDIR := /home/p1n9u/Desktop/embed/linux
PWD := $(shell pwd)
CR_C := arm-linux-gnueabihf-

default:
	make ARCH=arm CROSS_COMPILE=$(CR_C) -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
