# arduino-odroid

Arduino core for the ODROID

## Installation

- Install latest Arduino IDE for the Linux ARM from [www.arduino.cc/Main/Software](https://www.arduino.cc/en/Main/Software?target=_blank)
- Installation Guide : [www.arduino.cc/Guide/Linux](https://www.arduino.cc/en/Guide/Linux?target=_blank)
  - ODROID C1/XU4 : ARM 32bit
  - ODROID C2/N2 : ARM 64bit
- Open Terminal and execute   the following command (copy and paste the following command after $):

```bash
$ sudo apt update && sudo apt upgrade -y && sudo apt autoremove -y
```

```bash
$ sudo apt install -y git &&\
  git clone https://github.com/hhk7734/arduino-odroid.git ~/Arduino/hardware/hardkernel/odroid
```

- If you already open the Arduino IDE, Reopen Arduino IDE

- If you write and compile the code for the your Odroid on the desktop, additionally install a cross compiler.(copy and paste the following command after $)

```bash
$ echo "for the Odroid c1/xu4" &&\
  sudo apt install -y gcc-arm-linux-gnueabihf &&\
  sudo apt install -y g++-arm-linux-gnueabihf

$ echo "for the Odroid c2/n2" &&\
  sudo apt install -y gcc-aarch64-linux-gnu &&\
  sudo apt install -y g++-aarch64-linux-gnu
```

## setup

### select board

![board](./image/01.select_board.png){: .center}

### select programmer

![programmer](./image/02.select_programmer.png){: .center}

## passwd

If you don't want to input your passwd every upload, register user as a nopasswd user on the end of the sudoers file.

```bash
$ sudo visudo

...
odroid ALL=(ALL) NOPASSWD:ALL
```

## todo

- add core source
