KERNEL_HEADERS=/lib/modules/$(shell uname -r)/build
CC = gcc

TARGET := app
obj-m := mydriver.o

all : driver app

driver:
	make -C $(KERNEL_HEADERS) M=$(PWD) modules

app:
	$(CC) -o $@ $@.c

clean:
	make -C $(KERNEL_HEADERS) M=$(PWD) clean
	rm -f *.o $(TARGET)
