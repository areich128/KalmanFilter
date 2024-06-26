import serial

# Set up the serial connection (adjust 'COM3' to your Arduino's port)
ser = serial.Serial('COM3', 9600, timeout=1)

with open('output.txt', 'w') as file:
    while True:
        try:
            line = ser.readline().decode('utf-8').rstrip()
            if line:
                print(line)
                file.write(line + '\n')
                file.flush()
        except KeyboardInterrupt:
            print("Stopped by user")
            break

ser.close()