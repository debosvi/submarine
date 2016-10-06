#!/bin/bash 
# rootfs-build.sh
# v1.0

. `dirname $0`/basic-build.sh

cd $IMG_DIR

INSTANCE=$1

if [ "$INSTANCE" == "" ]; then
	die "Usage: $0 <NB>"
fi

NB=$(echo 10+$INSTANCE | bc -l)

if [ ! -f /sys/class/net/vcan0 ]; then
    $SUBMARINE_PROJECT_DIR/tools/qemu-canup
fi

#QEMU_CMD=qemu-system-i386
QEMU_CMD=/opt/projects/qemu/usr/bin/qemu-system-i386

QEMU_CONSOLE=-nographic
QEMU_CONSOLE_APPEND=console=ttyS0 

#QEMU_CONSOLE=-vga std

#CAN_PCI_ARGS="-device pci_can,chardev=canbus0,model=SJA1000"
CAN_PCI_ARGS="-device kvaser_pci,canbus=canbus0,host=vcan0"
#CAN_PCI_ARGS="-chardev can,id=sja1000,port=vcan0 -device kvaser_pci,canbus=canbus0,host=vcan0"

$QEMU_CMD -m 128 $QEMU_CONSOLE -k fr \
    -kernel ./vmlinuz -initrd $ROOTFS_INITRD.gz \
    -net nic,model=e1000,macaddr=52:54:00:12:34:$NB -net socket,mcast=230.0.0.1:1234 \
    $CAN_PCI_ARGS \
    -append "panic=1 $QEMU_CONSOLE_APPEND HOST=SUBMARINE EXPECTED_IP=10.0.2.$NB"
