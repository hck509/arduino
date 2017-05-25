import serial
import time
import sys

ser = serial.Serial('Com11', 9600, timeout=0)
#time.sleep(5)

rot = 0

print(sys.argv)

time.sleep(1)

count = 0
while 1:
    ser.write(bytes(str(sys.argv[1]) + "," + str(sys.argv[2]) + ";", 'UTF-8'))
    time.sleep(0.1)
    count = count + 1
    if count > 1:
        break;

#while 1:
    #rot += 1
    #ser.write(bytes(str(sys.argv[0]) + "," + str(sys.argv[1]) + ";", 'UTF-8'))
    #time.sleep(0.1)
    #if rot >= 179:
    #    break;

ser.close()