#!/bin/bash -x

MACHINE_TYPE=pic32mx7-max32
BIOS_IMG=PIC32/boot-max32.hex
ROOT_IMG=PIC32/hello-max32.hex
ROOT_IMG=PIC32/uart.hex

RAM_OPTS=-m 12
GEN_OPTS=-nographic -monitor none

qemu-system-mipsel -machine pic32mx7-max32 $RAM_OPTS $GEN_OPTS -serial stdio -bios $BIOS_IMG -kernel $ROOT_IMG

