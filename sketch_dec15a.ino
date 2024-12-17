const int buttonPin = 2;  // Pin connected to the push button
int buttonState = 0;      // Variable to store button state

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Pull-up resistor enabled
  Serial.begin(9600);              // Start serial communication
}

void loop() {
  buttonState = digitalRead(buttonPin);
  
  if (buttonState == LOW) {        // Button pressed (LOW with pull-up)
    Serial.println("START");       // Send signal to p5.js
    delay(500);                    // Debounce delay
  }
}
