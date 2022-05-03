import time
import serial

ser = serial.Serial(port = '/dev/ttyAMA0',
                    baudrate = 9600,
                    timeout = 1)

while True:
    data = input("입력 : ")

    print(ser.write(data.encode('utf-8')))
    print(ser.readall())
    
    if (data == 'q'):
        break

    time.sleep(2)
