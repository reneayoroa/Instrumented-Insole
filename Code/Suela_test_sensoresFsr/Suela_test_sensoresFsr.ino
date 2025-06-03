// Pin Definitions for ESP32-C3
const int s0 = 0;
const int s1 = 1;
const int s2 = 2;
const int s3 = 3;
const int muxSIG = 4; // Common signal pin (connected to analog input)

// Number of sensors to read
const int numSensors = 8; // Using channels 0–7
String output;
void setup() {
  // Set select pins as outputs
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);

  // Initialize serial monitor
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Hello from ESP32-C3!");
  
}

void loop() {
  //Serial.println("FSR Sensor Readings:");
  for (int i = 0; i < numSensors; i++) {
    setMuxChannel(i);                         // Set the channel on the multiplexer
    int fsrValue = analogRead(muxSIG);        // Read analog value from the selected FSR
    output.concat(fsrValue);
    if(i<(numSensors-1))
    {
      output.concat(", ");
    }

    delay(1); // Short delay for stable reading
  }
  output.concat("\n ");
  Serial.print(output);
  output = "";
  delay(100); // Wait before next round of readings
}

// Function to set multiplexer channel
void setMuxChannel(int channel) {
  digitalWrite(s0, bitRead(channel, 0));
  digitalWrite(s1, bitRead(channel, 1));
  digitalWrite(s2, bitRead(channel, 2));
  digitalWrite(s3, bitRead(channel, 3));
}
