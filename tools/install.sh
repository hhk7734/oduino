#!/bin/sh

if [ "$(id -u)" -ne 0 ]; then
    printf "Must run as root privileges.\n"
    exit 1
fi

if [ "x${SUDO_USER}" = "x" ]; then
    export SUDO_USER=root
fi

SCRIPT_PATH=$(dirname "$(realpath "$0")")

add-apt-repository -y ppa:hardkernel/ppa &&\
apt update

apt install -y build-essential \
    git \
    odroid-config \
    odroid-wiringpi \
    libwiringpi-dev \
    python3 \
    python3-tk

make -C "$SCRIPT_PATH/ttu0uart" &&\
make -C "$SCRIPT_PATH/ttu0uart" install

if ! grep -q spi: /etc/group ; then
    addgroup spi
fi

if ! grep -q i2c: /etc/group ; then
    addgroup i2c
fi

install -m 0644 "$SCRIPT_PATH/52-oduino.rules" /etc/udev/rules.d

chown root:spi /dev/spidev*
chmod 660 /dev/spidev*

chown root:i2c /dev/i2c-*
chmod 660 /dev/i2c-*

usermod -aG spi $SUDO_USER
usermod -aG i2c $SUDO_USER