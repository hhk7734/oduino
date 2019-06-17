# arduino-odroid

Arduino core for the ODROID

## Installation

- Install latest Arduino IDE for linux ARM from [arduino.cc](https://www.arduino.cc/en/Main/Software)
- Open Terminal and execute the following command (copy->paste and hit enter):

```bash
mkdir -p ~/Arduino/hardware/hardkernel && \
cd ~/Arduino/hardware/hardkernel && \
git clone https://github.com/hhk7734/arduino-odroid.git odroid
```

- Restart Arduino IDE

## FS

* cores/odroid : core source and header
* variants/ : pin map
* boards.txt
* platform.txt
* programmers.txt
