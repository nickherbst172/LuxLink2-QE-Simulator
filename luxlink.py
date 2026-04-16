import serial
import time

# Update 'COM3' to the port your Arduino is on (check Arduino IDE)
arduino_port = "COM3" 
baud_rate = 9600

try:
    ser = serial.Serial(arduino_port, baud_rate, timeout=1)
    print(f"Connected to LuxLink on {arduino_port}")
    
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()
            print(f"Quantum Event: {line}")
            
            # Optional: Log to a file for your portfolio
            with open("quantum_log.txt", "a") as f:
                f.write(f"{time.ctime()}: {line}\n")
                
except Exception as e:
    print(f"Error: {e}")