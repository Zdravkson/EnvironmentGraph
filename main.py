#!/usr/bin/env python3
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import serial
from sys import argv
from random import randint
from time import sleep


# Checks if all arguments there
if len(argv) != 3:
    print("python3 [PORT] [BAUD RATE]")
    exit()

# Apply theme for matplotlib
plt.style.use('fivethirtyeight')


# Initialize serial communication with arduino
arduino_serial = serial.Serial()
arduino_serial.baudrate = int(argv[2])
arduino_serial.port = argv[1]
arduino_serial.open()

# Default all to 0
temperature = []
humidity = []
heat_index = []

# Ignore first 3 line
for i in range(5):
    arduino_serial.readline()


def animate(i):
    plt.cla()
    try:
        raw_data = arduino_serial.readline().decode(
            "utf-8").replace("\r\n", "").split(",")
        temperature.append(raw_data[0])
        humidity.append(raw_data[1])
        heat_index.append(raw_data[2])

        print(raw_data)

    except:
        pass

    x1 = list(range(len(temperature)))
    x2 = list(range(len(humidity)))
    x3 = list(range(len(heat_index)))

    plt.plot(x1, temperature, label='Температура')
    plt.plot(x2, humidity, label='Влажност ваздуха')
    plt.plot(x3, heat_index, label='Реалан осећај температуре')

    plt.legend(loc='upper left')
    plt.tight_layout()


ani = FuncAnimation(plt.gcf(), animate, interval=1000)

plt.tight_layout()
plt.show()
