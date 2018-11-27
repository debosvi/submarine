# submarine
Boz submarine project

-- PREREQUISITES on Ubuntu --
make cmake gcc g++ unzip wget 
autoconf automake autogen
libtool

-- PREREQUISITES for Qemu building --
python-software-properties
pkg-config
zlib1g-dev libglib2.0-dev libpixman-1-dev

-- PREREQUISITES for Qemu runtime --
bridge-utils
openvpn

-- VCAN module

sudo modprobe vcan
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0

