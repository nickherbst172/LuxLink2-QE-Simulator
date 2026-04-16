import serial
import time
import random

# CHANGE 'COM3' to whatever your Arduino IDE says (e.g., COM4)
PORT = 'COM3' 

try:
    arduino = serial.Serial(port=PORT, baudrate=9600, timeout=1)
    print(f"✨ LuxCrypt Hardware Connected on {PORT}!")
except Exception as e:
    print(f"❌ Error: Could not connect. Is the Serial Monitor open in Arduino IDE? Close it first!")
    exit()

def start_luxcrypt(bits_to_generate=5):
    key = []
    print(f"\n--- LuxCrypt QKD Session Started ---")
    print(f"Target: {bits_to_generate} secure bits.")
    print("ACTION: Press your physical button to send a photon.")

    while len(key) < bits_to_generate:
        line = arduino.readline().decode('utf-8').strip()
        if line and "," in line:
            voltage, pressed = line.split(",")
            if pressed == "1":
                # Security Check
                if int(voltage) < 300:
                    print(f"⚠️  INTERCEPTION ALERT! Signal too weak ({voltage}). Bit discarded.")
                else:
                    bit = random.randint(0, 1)
                    key.append(bit)
                    print(f"✅ Bit {len(key)} Accepted! [Signal: {voltage} | Value: {bit}]")

    print(f"\n--- SUCCESS ---")
    print(f"Your Secret Quantum Key is: {key}")

if __name__ == "__main__":
    time.sleep(2)
    start_luxcrypt()