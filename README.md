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

[https://github.com/arduino/Arduino/wiki/Arduino-IDE-1.5-3rd-party-Hardware-specification](https://github.com/arduino/Arduino/wiki/Arduino-IDE-1.5-3rd-party-Hardware-specification)

## passwd

If you don't want to input your passwd every upload, you have two options.

### first option

```bash
sudo ln -s ~/Arduino/hardware /root/Arduino
```

```bash
sudo arduino
```

### secound option

```bash
sudo visudo

odroid ALL=(ALL) NOPASSWD:ALL
```

## todo

- add core source
- wiringPi -> C code
