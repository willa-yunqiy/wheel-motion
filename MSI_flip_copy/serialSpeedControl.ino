int motorTrans(int val) {
  int speed = 0;
  if (val >= 0) {
    digitalWrite(dir, LOW);
    // Serial.println("ccw");
    speed = min(val, 255);
  } else {
    digitalWrite(dir, HIGH);
    // Serial.println("cw");
    speed = min(abs(val), 255);
  }
  if (speed != 0) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW); 
  }
  prevVal = val;
  return speed;
}


void motorSpeedViaSerial() {
  //Check to see if anything is available in the serial receive buffer
  while (Serial.available() > 0) {
    static char message[MAX_MESSAGE_LENGTH];
    static unsigned int message_pos = 0;

    //Read the next available byte in the serial receive buffer
    char inByte = Serial.read();

  //Message coming in (check not terminating character) and guard for over message size
    if (inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1)){
      //Add the incoming byte to our message
      message[message_pos] = inByte;
      message_pos++;
    } else {
      //Add null character to string
      message[message_pos] = '\0';
      Serial.println(message);
      if (message[0] == 'b') {
        Serial.println("brake");
        digitalWrite(brake, HIGH);
      } else {
        digitalWrite(brake, LOW);
      }
      val = atoi(message); // between 0 and 255

      motorSpeed = motorTrans(val);

      // Reset for the next message
      message_pos = 0;
    }
  }
  // if (motorSpeed > 0) {
  //   lightupNumRGB(0,0,100,100);
  //   lightupNumRGB(1,0,0,0);
  // } else if (motorSpeed < 0) {
  //   lightupNumRGB(1,100,100,0);
  //   lightupNumRGB(0,0,0,0);
  // }
  analogWrite(motor, motorSpeed);
  delay(10);
}


void applyBrake() {
  digitalWrite(brake, HIGH);
}

void runAt(int motorspeed) {
  digitalWrite(brake, LOW);
  int s = motorTrans(motorspeed);
  analogWrite(motor, s);
}

void stopMotor() {
  analogWrite(motor, 0);
}
