// For the LED
int redLed = 11; 
int greenLed = 10;
int blueLed = 9; 
float RGB[3];

// For sound sensor
const int soundpin = A2;
const int threshold = 500;

// For light sensor
int ldrpin = 0;
int ambientLight;

// For button
int LED_PIN = 2;
int BUTTON_PIN = 4;
byte lastButtonState = LOW;
byte ledState = LOW;
unsigned long debounceDuration = 50;
unsigned long lastTimeButtonStateChanged = 0;
float x = 0;

void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  pinMode(soundpin, INPUT);
  pinMode(BUTTON_PIN, INPUT);
}

void lightSensor() {
  ambientLight = analogRead(ldrpin);
  if (ambientLight > 600) {
    analogWrite(redLed, RGB[0]);
    analogWrite(greenLed, RGB[1]);
    analogWrite(blueLed, RGB[2]);
  } else {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, LOW);
    digitalWrite(blueLed, LOW);
  }
}

void soundSensor() {
  int soundsens = analogRead(soundpin);
  if (soundsens >= threshold) {
    analogWrite(redLed, RGB[0]);
    analogWrite(greenLed, RGB[1]);
    analogWrite(blueLed, RGB[2]);
  } else {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, LOW);
    digitalWrite(blueLed, LOW);
  }
}

void loop() {
  x = x + 0.00001;
  RGB[0] = 255 * abs(sin(x));
  RGB[1] = 255 * abs(sin(x + PI/3));
  RGB[2] = 255 * abs(sin(x + (2 * PI) / 3));

  byte led = digitalRead(LED_PIN);
  if (led == LOW) {
    soundSensor();
  } else {
    lightSensor();
  }

  if (millis() - lastTimeButtonStateChanged > debounceDuration) {
    byte buttonState = digitalRead(BUTTON_PIN);
    if (buttonState != lastButtonState) {
      lastTimeButtonStateChanged = millis();
      lastButtonState = buttonState;
      if (buttonState == LOW) {
        ledState = (ledState == HIGH) ? LOW : HIGH;
        digitalWrite(LED_PIN, ledState);
      }
    }
  }
}
