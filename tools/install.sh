#!/bin/sh

# MIT License
#
# Copyright (c) 2019-2020 Hyeonki Hong <hhk7734@gmail.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

RED=$(tput setaf 1)
ORANGE=$(tput setaf 3)
BOLD=$(tput bold)
DEFAULT=$(tput sgr0)

if [ "$(id -u)" -ne 0 ]; then
    printf "Must run as root privileges. %s%s%s\n" \
        "${RED}${BOLD}" \
        "Try 'sudo $0'" \
        "${DEFAULT}" >&2
    exit 1
fi

if [ "x${SUDO_USER}" = "x" ]; then
    export SUDO_USER=${USER}
fi

SCRIPT_PATH=$(dirname "$(realpath "$0")")

isInstalled() {
    [ -n "$(command -v "$1" 2>/dev/null)" ]
}

existIn() {
    [ -n "$(find "$1" -name "$2" 2>/dev/null)" ]
}

printf "%s\nAdding hardkernel/ppa and installing required packages.\n%s" \
    "${ORANGE}${BOLD}" "${DEFAULT}"

if ! existIn "/etc/apt/sources.list.d" "*hardkernel-ubuntu-ppa*"; then
    add-apt-repository -y ppa:hardkernel/ppa
fi

apt update

DEPENDENCIES=""

if ! isInstalled odroid-config; then
    DEPENDENCIES="${DEPENDENCIES} odroid-config"
fi

if ! isInstalled git; then
    DEPENDENCIES="${DEPENDENCIES} git"
fi

if ! isInstalled gpio; then
    DEPENDENCIES="${DEPENDENCIES} libwiringpi-dev"
fi

if ! (isInstalled gcc && isInstalled make); then
    DEPENDENCIES="${DEPENDENCIES} build-essential"
fi

if ! isInstalled python3; then
    DEPENDENCIES="${DEPENDENCIES} python3"
fi

if ! (dpkg --list | grep -q python3-tk); then
    DEPENDENCIES="${DEPENDENCIES} python3-tk"
fi

eval "apt install -y $DEPENDENCIES"

printf "%s\nInstalling tty0uart.\n%s" "${ORANGE}${BOLD}" "${DEFAULT}"
sleep 0.5

make -C "$SCRIPT_PATH/tty0uart" &&
    make -C "$SCRIPT_PATH/tty0uart" install

printf "%s\nAdding udev rules and registering %s to spi, i2c group.\n%s" \
    "${ORANGE}${BOLD}" "${SUDO_USER}" "${DEFAULT}"
sleep 0.5

if ! grep -q spi: /etc/group; then
    groupadd -f spi
fi

if ! grep -q i2c: /etc/group; then
    groupadd -f i2c
fi

if ! grep -q gpio: /etc/group; then
    groupadd -f gpio
fi

if ! grep -q dialout: /etc/group; then
    groupadd -f dialout
fi

install -m 0644 "$SCRIPT_PATH/52-oduino.rules" /etc/udev/rules.d

usermod -aG spi "$SUDO_USER"
usermod -aG i2c "$SUDO_USER"
usermod -aG gpio "$SUDO_USER"
usermod -aG dialout "$SUDO_USER"

printf "%s\nPlease reboot before use!!!\n%s" "${ORANGE}${BOLD}" "${DEFAULT}"

while true; do
    printf "Would you like to reboot now[Y/n]? "
    read -r ans
    [ -z "$ans" ] && ans=y

    case "$ans" in
    [Yy]*)
        sync
        reboot
        break
        ;;
    [Nn]*) exit ;;
    *)
        printf "%sPlease answer \"y\" or \"n\".\n%s" "${RED}${BOLD}" \
            "${DEFAULT}"
        ;;
    esac
done
