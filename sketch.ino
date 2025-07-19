#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4     // DS18B20 data pin
#define RELAY_PIN 5        // Relay module control pin
#define LED_PIN 2          // LED to indicate heater state

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

enum HeaterState {
  IDLE,
  HEATING,
  STABILIZING,
  TARGET_REACHED,
  OVERHEAT
};

HeaterState currentState = IDLE;

// Thresholds
const float idleThreshold = 35.0;
const float targetTemp = 37.0;
const float lowerBound = 36.5;
const float overheatTemp = 38.0;

void setup() {
  Serial.begin(115200);
  sensors.begin();

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, LOW); // Heater OFF initially
  digitalWrite(LED_PIN, LOW);   // LED OFF initially
}

void loop() {
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" °C\t");

  updateState(temp);
  handleHeater(currentState);
  printState(currentState);

  delay(1000);
}

void updateState(float temp) {
  switch (currentState) {
    case IDLE:
      if (temp < idleThreshold)
        currentState = HEATING;
      break;

    case HEATING:
      if (temp >= lowerBound && temp < targetTemp)
        currentState = STABILIZING;
      else if (temp >= targetTemp && temp <= overheatTemp)
        currentState = TARGET_REACHED;
      else if (temp > overheatTemp)
        currentState = OVERHEAT;
      break;

    case STABILIZING:
      if (temp >= targetTemp && temp <= overheatTemp)
        currentState = TARGET_REACHED;
      else if (temp > overheatTemp)
        currentState = OVERHEAT;
      else if (temp < idleThreshold)
        currentState = HEATING;
      break;

    case TARGET_REACHED:
      if (temp > overheatTemp)
        currentState = OVERHEAT;
      else if (temp < lowerBound)
        currentState = HEATING;
      break;

    case OVERHEAT:
      if (temp <= targetTemp)
        currentState = STABILIZING;
      break;
  }
}

void handleHeater(HeaterState state) {
  if (state == HEATING) {
    digitalWrite(RELAY_PIN, HIGH); // Heater ON
    digitalWrite(LED_PIN, HIGH);   // LED ON
  } else {
    digitalWrite(RELAY_PIN, LOW);  // Heater OFF
    digitalWrite(LED_PIN, LOW);    // LED OFF
  }
}

void printState(HeaterState state) {
  switch (state) {
    case IDLE: Serial.println("State: Idle."); break;
    case HEATING: Serial.println("State: Heating....."); break;
    case STABILIZING: Serial.println("State: Stabilizing"); break;
    case TARGET_REACHED: Serial.println("State: Target Reached!"); break;
    case OVERHEAT: Serial.println("State: Overheating!!!!!"); break;
  }
}
