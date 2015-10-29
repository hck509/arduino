import serial
import time

ser = serial.Serial('Com11', 9600, timeout=0)
#time.sleep(5)

rot = 0

while 1:
    rot += 1
    ser.write(bytes(str(rot) + ",50;", 'UTF-8'))
    time.sleep(0.1)
    if rot >= 179:
        break;

ser.close()