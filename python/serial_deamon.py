import serial
import time
import sys

ser = serial.Serial('Com11', 9600, timeout=0)
time.sleep(1)

while 1:
    f = open('input.txt', 'r');
    line = f.readline()
    print(line)
    #ser.write(bytes(str(sys.argv[1]) + "," + str(sys.argv[2]) + ";", 'UTF-8'))
    ser.write(bytes(line, 'UTF-8'))
    time.sleep(0.1)

ser.close()