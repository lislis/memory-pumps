/*
 * Memory pumps
 *
 * two water level sensors, two transistors, two motors/pumps
 */

#define WATER_LEVEL_1 A0
#define WATER_LEVEL_2 A1 

#define POWER_PIN_1 7
#define POWER_PIN_2 8

#define SWITCH_1 4
#define SWITCH_2 5


void setup() {
  pinMode(POWER_PIN_1, OUTPUT);
  pinMode(POWER_PIN_2, OUTPUT);
  digitalWrite(POWER_PIN_1, LOW);
  digitalWrite(POWER_PIN_2, LOW);
  Serial.begin(115200);
  Serial.println("setup done");
}

void loop() {
  Serial.print(0);
  Serial.print(",");
  Serial.print(measure_water_level(POWER_PIN_1, WATER_LEVEL_1));
  Serial.print(",");
  Serial.print(measure_water_level(POWER_PIN_2, WATER_LEVEL_2));
  Serial.print(",");
  Serial.println("1023");
  delay(800);
}

int measure_water_level(int power, int pin) {
  int val;
  digitalWrite(power, HIGH);
  delay(10);
  val = analogRead(pin);
  delay(2);
  digitalWrite(power, LOW);
  return val;
}
