/*
 * PROJECT: LuxLink2 - Quantum Key Distribution (QKD) Simulator
 * HARDWARE: Arduino Uno, 2x LEDs (Pins 2, 3), 1x Trigger (Pin 4)
 * LOGIC: Uses physical entropy to collapse a shared wavefunction 
 * and streams the resulting bit to Python for key generation.
 */

// Pin Definitions
const int qubitA = 2; // LED A
const int qubitB = 3; // LED B
const int triggerPin = 4; // Touch this to GND to "Measure"

void setup() {
  pinMode(qubitA, OUTPUT);
  pinMode(qubitB, OUTPUT);
  
  // Internal Pullup: Measurement happens when Pin 4 hits Ground
  pinMode(triggerPin, INPUT_PULLUP);
  
  // Seed randomness using atmospheric noise on an empty analog pin
  randomSeed(analogRead(A5)); 
  
  Serial.begin(9600);
  Serial.println("--- LUXLINK2 SYSTEM INITIALIZED ---");
  Serial.println("Status: Superposition Active");
  Serial.println("Action: Ground Pin 4 to generate a secure bit...");
}

void loop() {
  // --- STAGE 1: SUPERPOSITION ---
  // The bits are "undecided" and flickering rapidly.
  while(digitalRead(triggerPin) == HIGH) {
    digitalWrite(qubitA, random(0, 2)); 
    digitalWrite(qubitB, random(0, 2));
    delay(20); // Slightly faster flicker for a better visual effect
  }

  // --- STAGE 2: THE MEASUREMENT (COLLAPSE) ---
  // The system collapses into a single, correlated state.
  int collapsedState = random(0, 2); 

  // --- STAGE 3: CORRELATION & OUTPUT ---
  // Physical feedback
  digitalWrite(qubitA, collapsedState);
  digitalWrite(qubitB, collapsedState);

  // MACHINE PROTOCOL: This is the specific line your Python script is listening for!
  Serial.print("COLLAPSE:"); 
  Serial.println(collapsedState); 

  // HUMAN PROTOCOL: This is just for you to read in the Serial Monitor.
  Serial.print(">> Result: |");
  Serial.print(collapsedState);
  Serial.println("> - Bit Streamed to LuxLink2 Engine.");

  // Hold for 2 seconds so you can see the matching LEDs
  delay(2000); 

  Serial.println("Resetting to Superposition...\n");
}