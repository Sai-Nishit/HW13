// Pin Definitions for LEDs
const int greenLED = 4;
const int yellowLED = 3;
const int blueLED = 5;
const int redLED = 2;

// Sensor Pins
const int trigRight = 7, echoRight = 8;  // HC-SR04 Right
const int pingTop = 11;                  // Parallax Ping Top
const int buttonPin = 6;                 // Push Button

const float maxRange = 15.4;             // Maximum sensor range in cm

void setup() {
  Serial.begin(9600); // Start Serial Communication
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  // Initialize all LEDs to OFF
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, LOW);

  pinMode(trigRight, OUTPUT);
  pinMode(echoRight, INPUT);
  pinMode(pingTop, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

// Function to read distance from HC-SR04
long readHCSR04(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH) * 0.034 / 2; // Convert to cm
}

// Function to read distance from Parallax Ping
long readParallaxPing(int signalPin) {
  pinMode(signalPin, OUTPUT);
  digitalWrite(signalPin, LOW);
  delayMicroseconds(2);
  digitalWrite(signalPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(signalPin, LOW);
  pinMode(signalPin, INPUT);
  return pulseIn(signalPin, HIGH) * 0.034 / 2; // Convert to cm
}

// Function to process serial commands
void processCommand(String command) {
  command.trim(); // Remove trailing spaces or newlines

  if (command.startsWith("LED_ON")) {
    int led = command.substring(7).toInt();
    if (led == 4) digitalWrite(greenLED, HIGH);
    else if (led == 3) digitalWrite(yellowLED, HIGH);
    else if (led == 5) digitalWrite(blueLED, HIGH);
  } else if (command.startsWith("LED_OFF")) {
    int led = command.substring(8).toInt();
    if (led == 4) digitalWrite(greenLED, LOW);
    else if (led == 3) digitalWrite(yellowLED, LOW);
    else if (led == 5) digitalWrite(blueLED, LOW);
  } else if (command == "RED_BLINK") {
    blinkRedLED();
  }
}

// Blink the red LED for "Game Over"
void blinkRedLED() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(redLED, HIGH);
    delay(500);
    digitalWrite(redLED, LOW);
    delay(500);
  }
}

void loop() {
  // Read sensor distances
  float top = readParallaxPing(pingTop);
  float right = readHCSR04(trigRight, echoRight);

  // Scale readings to max range
  top = min(top, maxRange);
  right = min(right, maxRange);

  // Read button state
  int buttonState = digitalRead(buttonPin);

  // Send sensor data to p5.js
  Serial.print(top);
  Serial.print(",");
  Serial.print(right);
  Serial.print(",");
  Serial.print(buttonState);
  Serial.println();

  // Check for incoming serial commands
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    processCommand(command);
  }

  delay(50); // Delay to stabilize readings
}
