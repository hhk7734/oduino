#!/bin/sh

if [ "$(id -u)" -ne 0 ]; then
    printf "Must run as root privileges.\n"
    exit 1
fi

if [ "x${SUDO_USER}" = "x" ]; then
    export SUDO_USER=root
fi

YELLOW_BOLD=$(tput setaf 3 && tput bold)
NORMAL=$(tput sgr0)

SCRIPT_PATH=$(dirname "$(realpath "$0")")

printf "\n%s\n" "${YELLOW_BOLD}Adding hardkernel/ppa \
and installing required packages.${NORMAL}"

add-apt-repository -y ppa:hardkernel/ppa &&\
apt update

apt install -y build-essential \
    git \
    odroid-config \
    odroid-wiringpi \
    libwiringpi-dev \
    python3 \
    python3-tk

printf "\n%s\n" "${YELLOW_BOLD}Installing tty0uart.${NORMAL}"

make -C "$SCRIPT_PATH/tty0uart" &&\
make -C "$SCRIPT_PATH/tty0uart" install

printf "\n%s\n" "${YELLOW_BOLD}Adding udev rules \
and registering $SUDO_USER to spi, i2c group.${NORMAL}"

if ! grep -q spi: /etc/group ; then
    addgroup spi
fi

if ! grep -q i2c: /etc/group ; then
    addgroup i2c
fi

install -m 0644 "$SCRIPT_PATH/52-oduino.rules" /etc/udev/rules.d

usermod -aG spi $SUDO_USER
usermod -aG i2c $SUDO_USER

printf "\n%s\n" "${YELLOW_BOLD}Please reboot before use!!!${NORMAL}"

whiptail --yesno "Would you like to reboot now?" 20 60
BUTTON=$?
if [ $BUTTON -eq 0 ]; then
    # Yes
    sync
    reboot
fi