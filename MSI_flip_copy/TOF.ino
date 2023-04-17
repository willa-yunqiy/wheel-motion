// void setupTOF() {
//   while (! Serial) {
//     delay(1);
//   }
  
//   Serial.println("Adafruit VL53L0X test");
//   if (!lox.begin()) {
//     Serial.println(F("Failed to boot VL53L0X"));
//     while(1);
//   }
//   // power 
//   Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
// }

// int readingTOF() {
//   VL53L0X_RangingMeasurementData_t measure;
    
//   lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

//   if (measure.RangeStatus != 4) {  // phase failures have incorrect data
//     Serial.println(measure.RangeMilliMeter);
//   } else {
//     Serial.println(" out of range ");
//   }
//   return measure.RangeMilliMeter;

// }

// void oneTOF() {
//   int dist = readingTOF();
//   if (dist < 100 && dist > 30) {
//     runAtFor(120, 1500);
//     applyBrakeFor(50);
//     stopFor(10);
//   } else {
//     analogWrite(motor, 0);
//   }
// }

void setID() {
  Serial.println("before everything");
  // all reset
  digitalWrite(SHT_LOX1, LOW);    
  digitalWrite(SHT_LOX2, LOW);
  delay(10);
  // all unreset
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  // activating LOX1 and resetting LOX2
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);

  Serial.println("before LOX1");
  // initing LOX1
  if(!lox1.begin(LOX1_ADDRESS)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while(1);
  }
  delay(10);

  Serial.println("before LOX2");
  // activating LOX2
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  //initing LOX2
  if(!lox2.begin(LOX2_ADDRESS)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while(1);
  }
  Serial.println("done with setting up LOX");
}

void readSensor1() {
  lox1.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!
  // print sensor one reading
  Serial.print(F("1: "));
  if(measure1.RangeStatus != 4) {     // if not out of range
    int dist1 = measure1.RangeMilliMeter;
    Serial.print(dist1);
    if (dist1 < 200 && dist1 > 150) {
      lightupNumRGB(0,150,150,0);
    } else {
      Serial.println("dfdf");
      lightupNumRGB(0,0,0,0);
    }
  } else {
    Serial.print(F("Out of range"));
    lightupNumRGB(0,0,0,0);
  }
  
  Serial.print(F(" "));

}

void readSensor2() {
  lox2.rangingTest(&measure2, false); // pass in 'true' to get debug data printout!
  // print sensor two reading
  Serial.print(F("2: "));
  if(measure2.RangeStatus != 4) {
    int dist2 = measure2.RangeMilliMeter;
    Serial.print(dist2);
    if (dist2 < 200 && dist2 > 150) {
      lightupNumRGB(1,0,0,150);
    } else {
      lightupNumRGB(1,0,0,0);
    }
  } else {
    Serial.print(F("Out of range"));
    lightupNumRGB(1,0,0,0);
  }
  
  Serial.println();  
}

// void read_dual_sensors() {
  
//   lox1.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!
//   lox2.rangingTest(&measure2, false); // pass in 'true' to get debug data printout!

//   // print sensor one reading
//   Serial.print(F("1: "));
//   if(measure1.RangeStatus != 4) {     // if not out of range
//     Serial.print(measure1.RangeMilliMeter);
//   } else {
//     Serial.print(F("Out of range"));
//   }
  
//   Serial.print(F(" "));

//   // print sensor two reading
//   Serial.print(F("2: "));
//   if(measure2.RangeStatus != 4) {
//     Serial.print(measure2.RangeMilliMeter);
//   } else {
//     Serial.print(F("Out of range"));
//   }
  
//   Serial.println();
// }

void dualTOF() {
  readSensor1();
  readSensor2();
}

void proxemicInteraction() {
  
  lox1.rangingTest(&measure1, false);
  lox2.rangingTest(&measure2, false);
  
  int dist1 = measure1.RangeMilliMeter;
  int dist2 = measure2.RangeMilliMeter;
  int speed = 0;

  if (measure1.RangeStatus != 4) {  // if not out of range
    if (dist1 < 200 && dist1 > 150) {
      motorOn = true;
    } 
  
  // else if (measure2.RangeStatus != 4) {  // if not out of range
  //   if (dist2 < 200 && dist2 > 150) {
  //     if (!motorOn) {
  //       // Turn on the motor pin and record the start time
  //       lightupNumRGB(1,0,0,150);
  //       runAt(-speed);
  //       motorStartTime = millis();
  //       motorOn = true;
  //     } else if (millis() - motorStartTime >= 2000) {
  //       // Turn on the brake pin after 2 seconds and turn off the motor pin
  //       applyBrake();
  //       delay(50);  // Wait for a short time for the brake to engage
  //       stopMotor();  // Double check the motor pin is off
  //       motorOn = false;
  //     }
  //   } 
  } 
}

