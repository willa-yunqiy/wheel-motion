#include <Wire.h>
#include <Servo.h>
#include "Adafruit_VL53L0X.h"

// address we will assign if dual sensor is present
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31

// set the pins to shutdown
#define SHT_LOX1 12
#define SHT_LOX2 13

// objects for the vl53l0x
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();

// this holds the measurement
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;

const unsigned int MAX_MESSAGE_LENGTH = 12;
//Create a place to hold the incoming message

String InBytes;
int val = 0;
int motorSpeed = 0;

#define motor    9  // pwm pin for motor to roll
#define brake    5  // 
#define dir    7    // 

double prevVal = 0;
int currDir = 0;
String str = "0";

// neopixel parameters
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN       A2
#define NUMPIXELS 2 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

unsigned long motorStartTime;  // Start time of the motor pin
bool motorOn = false;     // Motor pin status 

int r = 0;
int g = 0;
int b = 0;
int lednum = 0;
int speed = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("going to run setID");
  setID();
  Serial.println("finished setID");
  setupNeo();
}

void loop() {
  // dualTOF();
  // readSensor1();
  // readSensor2();

  // motorSpeedViaSerial();
  // proxemicInteraction();
   
  lox1.rangingTest(&measure1, false);
  lox2.rangingTest(&measure2, false);
  
  int dist1 = measure1.RangeMilliMeter;
  int dist2 = measure2.RangeMilliMeter;
  


  if (motorOn == false) {
    if (measure2.RangeStatus != 4) {  // if not out of range
      if (dist2 < 200 && dist2 > 150) {
        motorOn = true;
        motorStartTime = millis();
        lednum = 0;
        speed = 120;
        r = 0;
        g = 100;
        b = 100;
      } 
    }
    if (measure1.RangeStatus != 4) {  // if not out of range
      if (dist1 < 200 && dist1 > 150) {
        motorOn = true;
        speed = -120;
        motorStartTime = millis();
        lednum = 1;
        r = 100;
        g = 100;
        b = 0;
      } 
    }
  }

  if (motorOn) {
    // Turn on the motor pin and record the start time
    lightupNumRGB(lednum,r,g,b);
    runAt(speed);
    Serial.println("LED");
    if (millis() - motorStartTime >= 3000) {
      // Turn on the brake pin after 2 seconds and turn off the motor pin
      applyBrake();
      delay(50);  // Wait for a short time for the brake to engage
      stopMotor();  // Double check the motor pin is off
      digitalWrite(brake, LOW);
      motorOn = false;
      lightupNumRGB(0,0,0,0);
      Serial.println("brake applied");
    }
  }
}
