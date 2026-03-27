#include <OneWire.h>
#include <DallasTemperature.h>

// ---------------- PIN DEFINITIONS ----------------
#define ACS_PIN A2        // ACS712 output
#define ONE_WIRE_BUS 2    // DS18B20 data pin

// ---------------- SENSOR SETUP ----------------
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// ---------------- CALIBRATION ----------------
float sensitivity = 0.066;   // 30A ACS712 = 66mV/A
float offsetVoltage = 2.5;   // Default midpoint (adjust after calibration)

// ---------------- VARIABLES ----------------
float current = 0;
float temperature = 0;

unsigned long startTime;

// ---------------- FUNCTIONS ----------------

// Read current from ACS712
float readCurrent() {
  int adc = analogRead(ACS_PIN);
  float voltage = adc * (5.0 / 1023.0);
  float current = (voltage - offsetVoltage) / sensitivity;
  return current;
}

// Read temperature from DS18B20
float readTemperature() {
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}

// ---------------- SETUP ----------------
void setup() {
  Serial.begin(9600);
  sensors.begin();

  Serial.println("WIRE HEATING TEST START");
  Serial.println("Time(s), Current(A), Temp(C)");

  startTime = millis();
}

// ---------------- LOOP ----------------
void loop() {

  // Time in seconds
  unsigned long currentTime = (millis() - startTime) / 1000;

  // Read sensors
  current = readCurrent();
  temperature = readTemperature();

  // Print data
  Serial.print(currentTime);
  Serial.print(", ");
  Serial.print(current);
  Serial.print(", ");
  Serial.println(temperature);

  delay(1000);
}