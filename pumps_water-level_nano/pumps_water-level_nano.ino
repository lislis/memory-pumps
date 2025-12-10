/*
 * Memory pumps
 *
 * two water level sensors, two transistors, two motors/pumps
 */

#define TIMER_LENGTH 2000

struct Pump {
  int sensorPin;
  int powerPin;
  int switchPin;
  int sensorReading;
  bool powerState;
  bool switchState;
  unsigned long timerLength;
  bool isTimerRunning;
  unsigned long timerStart;
  unsigned long timerElapsed;
};

struct Pump pump1, pump2;

void setup() {
  init_pump(pump1, A0, 7, 4);
  init_pump(pump2, A1, 8, 5);

  Serial.begin(115200);
  Serial.println("setup done");
}

void loop() {
  measure_water_level(pump1);
  measure_water_level(pump2);

  if (pump1.sensorReading > 300) {
    pump1.switchState = HIGH;
    digitalWrite(pump1.switchPin, pump1.switchState);
  } else if (pump1.sensorReading < 200) {
    pump1.switchState = LOW;
    digitalWrite(pump1.switchPin, pump1.switchState);
  }


  Serial.print(0);
  Serial.print(",");
  Serial.print(pump1.sensorReading);
  Serial.print(",");
  Serial.print(pump2.sensorReading);
  Serial.print(",");
  Serial.println("1023");
  delay(800);
}

void measure_water_level(Pump& p) {
  digitalWrite(p.powerPin, HIGH);
  delay(10);
  p.sensorReading = analogRead(p.sensorPin);
  delay(2);
  digitalWrite(p.powerPin, LOW);
}

void init_pump(Pump& p, int sP, int pP, int swP) {
  p.sensorPin = sP;
  p.powerPin = pP;
  p.switchPin = swP;
  p.sensorReading = 0;
  p.powerState = LOW;
  p.switchState = LOW;
  p.timerLength = TIMER_LENGTH;
  p.isTimerRunning = false;

  pinMode(p.powerPin, OUTPUT);
  pinMode(p.switchPin, OUTPUT);
  digitalWrite(p.powerPin, LOW);
  digitalWrite(p.switchPin, LOW);
}

