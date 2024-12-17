let serial;                // Serial communication object
let animationStarted = false;

// Variables from your original sketch
let size;
let counter = 0;

function setup() {
  createCanvas(800, 600);  // Adjust the canvas size as needed
  background(0);           // Set the background
  
  // Serial Communication setup
  serial = new p5.SerialPort();
  serial.open('/dev/tty.usbmodem21101');    // Replace with your serial port name
  serial.on('data', serialEvent); 
  
  size = width / 2;
}

function draw() {
  if (animationStarted) {
    background(0);  // Reset background
    stroke(255);
    noFill();
    ellipse(width / 2, height / 2, size, size); 
    
    // Animation logic
    size -= 1;
    if (size <= 0) {
      size = width / 2;
      counter++;
    }
    
    // Display counter
    fill(255);
    textSize(24);
    textAlign(CENTER, CENTER);
    text(`Count: ${counter}`, width / 2, height / 2);
  } else {
    // Static message when animation is not running
    fill(255);
    textSize(24);
    textAlign(CENTER, CENTER);
    text("Press the button to start animation", width / 2, height / 2);
  }
}

// Function to handle serial data events
function serialEvent() {
  let data = serial.readLine().trim();
  if (data === "START") {
    animationStarted = true; // Start the animation
  }
}
