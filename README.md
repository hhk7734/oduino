# Oduino

Arduino core for the ODROID

## Installation

### OS

Supports Ubuntu MATE desktop.

Installation Guide and OS download link: <a href="https://wiki.odroid.com/getting_started/os_installation_guide" target=_blank>https://wiki.odroid.com/getting_started/os_installation_guide</a>

### Arduino

- Download latest Arduino IDE for the Linux ARM from <a href="https://www.arduino.cc/en/Main/Software" target=_blank>https://www.arduino.cc/en/Main/Software</a>
  - ODROID C1/XU4 : ARM 32bit
  - ODROID C2/N2 : ARM 64bit
- Installation Guide : <a href="https://www.arduino.cc/en/Guide/Linux" target=_blank>https://www.arduino.cc/en/Guide/Linux</a>

### Oduino

Open Terminal and execute the following command (copy and paste the following command to the termianl):

```bash
git clone --recursive https://github.com/hhk7734/oduino.git \
    ~/Arduino/hardware/hardkernel/odroid &&\
sudo ~/Arduino/hardware/hardkernel/odroid/tools/install.sh
```

If you already opened the Arduino IDE, Close and reopen the Arduino IDE.

## Setup

* Tools -> Board: -> ODROID
* Tools -> Port: -> /dev/ttyHK0
* Tools -> Programmer: -> Bridge
