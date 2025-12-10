/*
 * Memory pumps
 *
 * two water level sensors, two transistors, two motors/pumps, two buttons
 */

#define TIMER_LENGTH 3500
#define MAX_WATER_LEVEL 950

struct Pump {
  int sensorPin;
  int powerPin;
  int switchPin;
  int buttonPin;
  int sensorReading;
  bool powerState;
  bool switchState;
  bool buttonState;
  unsigned long timerLength;
  bool isTimerRunning;
  unsigned long timerStart;
  unsigned long timerElapsed;
};

struct Pump pump1, pump2;

void setup() {
  init_pump(pump1, A0, 7, 4, 10);
  init_pump(pump2, A1, 8, 5, 11);

  Serial.begin(115200);
  Serial.println("setup done");
}

void loop() {
  update_pump(pump1);
  update_pump(pump2);

  Serial.print(pump2.buttonState);
  Serial.print(",");
  Serial.print(0);
  Serial.print(",");
  Serial.print(pump1.sensorReading);
  Serial.print(",");
  Serial.print(pump2.sensorReading);
  Serial.print(",");
  Serial.println("1023");
  delay(80);
}

void update_pump(Pump& p) {
  measure_water_level(p);
  update_timer(p);
  read_button(p);
  operate_pump(p);
}

void operate_pump(Pump& p) {
  // the sensor reading is a safety guard here
  if (p.isTimerRunning && p.sensorReading < MAX_WATER_LEVEL) {
   digitalWrite(p.switchPin, HIGH); 
  } else {
    digitalWrite(p.switchPin, LOW); 
  }
}

void update_timer(Pump& p) {
  if (p.isTimerRunning) {
    p.timerElapsed = millis() - p.timerStart;
    if (p.timerElapsed >= p.timerLength) {
      p.isTimerRunning = false;
    }
  }
}

void read_button(Pump& p) {
  if (p.buttonState == 0 && digitalRead(p.buttonPin) == 1) {
    if (!p.isTimerRunning) {
      p.timerStart = millis();
      p.isTimerRunning = true;
    }
  }
  p.buttonState = digitalRead(p.buttonPin);
}

void measure_water_level(Pump& p) {
  digitalWrite(p.powerPin, HIGH);
  delay(10);
  p.sensorReading = analogRead(p.sensorPin);
  delay(2);
  digitalWrite(p.powerPin, LOW);
}

void init_pump(Pump& p, int sP, int pP, int swP, int bP) {
  p.sensorPin = sP;
  p.powerPin = pP;
  p.switchPin = swP;
  p.buttonPin = bP;
  p.sensorReading = 0;
  p.powerState = LOW;
  p.switchState = LOW;
  p.buttonState = 0;
  p.timerLength = TIMER_LENGTH;
  p.isTimerRunning = false;

  pinMode(p.buttonPin, INPUT);
  pinMode(p.powerPin, OUTPUT);
  pinMode(p.switchPin, OUTPUT);
  digitalWrite(p.powerPin, LOW);
  digitalWrite(p.switchPin, LOW);
}

