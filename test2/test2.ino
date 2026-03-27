#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

// ---------------- PIN DEFINITIONS ----------------
#define ACS_PIN A2
#define ONE_WIRE_BUS 2

// ---------------- SENSOR SETUP ----------------
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// ---------------- LCD SETUP (16x2) ----------------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------------- CALIBRATION ----------------
float sensitivity = 0.066;   // 30A ACS712
float offsetVoltage = 2.5;

// ---------------- VARIABLES ----------------
float current = 0;
float temperature = 0;
unsigned long startTime;

// ---------------- FUNCTIONS ----------------

// Read current
float readCurrent() {
  int adc = analogRead(ACS_PIN);
  float voltage = adc * (5.0 / 1023.0);
  float current = (voltage - offsetVoltage) / sensitivity;
  return current;
}

// Read temperature (fixed)
float readTemperature() {
  sensors.requestTemperatures();
  delay(200);  // important for stable reading

  float temp = sensors.getTempCByIndex(0);

  if (temp == DEVICE_DISCONNECTED_C) {
    return -127; // error flag
  }

  return temp;
}

// ---------------- SETUP ----------------
void setup() {
  Serial.begin(9600);
  sensors.begin();

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Wire Tester");
  lcd.setCursor(0,1);
  lcd.print("Initializing...");
  delay(2000);

  lcd.clear();

  Serial.println("WIRE HEATING TEST START");
  Serial.println("Time(s), Current(A), Temp(C)");

  startTime = millis();
}

// ---------------- LOOP ----------------
void loop() {

  unsigned long currentTime = (millis() - startTime) / 1000;

  current = readCurrent();
  temperature = readTemperature();

  // -------- SERIAL OUTPUT --------
  Serial.print(currentTime);
  Serial.print(", ");
  Serial.print(current);
  Serial.print(", ");
  Serial.println(temperature);

  // -------- LCD DISPLAY (16x2) --------
  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(currentTime);
  lcd.print("s ");

  lcd.print("I:");
  lcd.print(current,1);
  lcd.print("A ");

  lcd.setCursor(0,1);
  lcd.print("Temp:");

  if (temperature == -127) {
    lcd.print("Err   ");
  } else {
    lcd.print(temperature,1);
    lcd.print("C ");
  }

  // Status
  if (temperature > 60) {
    lcd.print("HOT");
  } else {
    lcd.print("OK ");
  }

  delay(1000);
}