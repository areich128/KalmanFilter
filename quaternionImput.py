import serial
import time

# Establish the connection to the Arduino
# Replace 'COM3' with the serial port your Arduino is connected to
ser = serial.Serial('COM3', 9600)
time.sleep(2)  # Wait for the connection to establish

output_file = 'quaternion_data.txt'

try:
    with open(output_file, 'a') as file:  # Using append mode
        while True:
            if ser.in_waiting > 0:
                line = ser.readline().decode('utf-8').strip()
                # Validate the input to ensure it has four float values
                try:
                    data = [float(num) for num in line.split(',')]
                    if len(data) == 4:
                        file.write(f"{data[0]:.2f},{data[1]:.2f},{data[2]:.2f},{data[3]:.2f}\n")
                        file.flush()  # Flush after every write operation
                        print(f"Recorded: {line}")
                    else:
                        print("Incorrect number of elements in line.")
                except ValueError:
                    print("Failed to parse floats from line.")
except KeyboardInterrupt:
    print("Program interrupted by user.")
finally:
    ser.close()
    print("Serial connection closed.")
