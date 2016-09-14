
SHELL=/bin/bash

CROSS_PREFIX?=i686-elf-

CC=$(CROSS_PREFIX)gcc
AS=$(CROSS_PREFIX)as

CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS=-ffreestanding -O2 -nostdlib
LIBS=-lgcc

OBJS=boot.o kernel.o

TARGET=myos
ISODIR_NAME=isodir

all: $(TARGET).iso

$(TARGET).iso: $(TARGET).bin grub.cfg
	mkdir -p $(ISODIR_NAME)/boot/grub
	cp $(TARGET).bin $(ISODIR_NAME)/boot/myos.bin
	cp grub.cfg $(ISODIR_NAME)/boot/grub/grub.cfg
	grub-mkrescue -o $(TARGET).iso $(ISODIR_NAME)
	
check: $(TARGET).bin
	if [ `grub-file --is-x86-multiboot $(shell pwd)/$(TARGET).bin` ]; then echo -e "multiboot confirmed"; else echo -e "the file is not multiboot"; fi
	
qemu-kernel: $(TARGET).bin
	qemu-system-i386 -kernel $(TARGET).bin
	
qemu-iso: $(TARGET).iso
	qemu-system-i386 -cdrom $(TARGET).iso
	
grub.cfg: grub.cfg.tmpl
	sed -e s/%TARGET%/$(TARGET)/g $@.tmpl > $@
	
$(TARGET).bin: $(OBJS) linker.ld
	$(CC) -T linker.ld -o $@ $(LDFLAGS) $(OBJS) $(LIBS)
	
boot.o: boot.s
	$(AS) $^ -o $@
	
kernel.o: kernel.c
	$(CC) $(CFLAGS) -c $^ -o $@
	
clean:
	rm -rf $(TARGET).* *.o $(ISODIR_NAME) grub.cfg
	 	