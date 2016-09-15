#!/bin/bash

MACHINE_TYPE=pic32mx7-max32
BIOS_IMG=boot-max32.hex
ROOT_IMG=hello-max32.hex

qemu-system-mipsel -machine $MACHINE_TYPE -serial stdio -bios $BIOS_IMG -kernel $ROOT_IMG

