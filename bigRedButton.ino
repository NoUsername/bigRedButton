const int SWITCH_PIN = 8;
const int basePin = 9;
  
//// LEDS

void turnLed(int idx, bool state) {
  if (idx == 0) {
    analogWrite(basePin, state ? 255 : 0);
  } else {
    digitalWrite(basePin + idx, state ? HIGH : LOW);
  }
}

void allYellow(bool state) {
  for (int i=0; i<4; i++) {
    turnLed(1 + i, state ? HIGH : LOW);
  }
}

void allLeds(bool state) {
  for (int i=0; i<5; i++) {
    turnLed(i, state ? HIGH : LOW);
  }
}

void buttonLight(bool state) {
  turnLed(0, state);
}

void buttonLight(int value) {
  analogWrite(basePin, value);
}

//// BUTTON

bool isButtonPressed() {
  return digitalRead(SWITCH_PIN) == HIGH;
}

void checkButton() {
  if (isButtonPressed()) {
    allLeds(true);
  }
}

void wait() {
  int steps = 20;
  int MAX = 255;
  int MIN = 10;
  int d = 60;
  while (!isButtonPressed()) {
    for (int i=0; i<steps*2 && !isButtonPressed(); i++) {
      delay(d);
      if (i < steps) {
        buttonLight((int)map(i, 0, steps, MIN, MAX));
      } else {
        buttonLight((int)map(i - steps, steps, 0, MIN, MAX));
      }
    }
    // little extra, looks cooler
    delay(5*d);
  }
}

void warmup() {
  allLeds(false);
  int d = 250;
  for (int i=0; i<10; i++) {
    delay(d);
    turnLed(1, true); turnLed(2, false); turnLed(3, true); turnLed(4, false);
    delay(d);
    turnLed(1, false); turnLed(2, true); turnLed(3, false); turnLed(4, true);
  }  
}

void runAround(int d, int rounds) {
  for (int i=0; i<rounds; i++) {
    for (int j=0; j<4; j++) {
      delay(d); 
      allYellow(false);
      turnLed(1+j, true);
    }
  }
}

void countDown() {
  buttonLight(true);
  int countTo=30;
  for (int i=0; i<countTo; i++) {
    int dTime = 15*(countTo-i);
    allYellow(true);
    delay(dTime);
    allYellow(false);
    delay(dTime);
    buttonLight((i/2) %2 == 0);
  }
}

void explode() {
  int d = 25;
  for (int l=0; l<20; l++) {
    for (int i=0; i<5; i++) {
     delay(d);
     turnLed(i, HIGH);
     delay(d);
     turnLed(i, LOW);
    }
  }
}

void setup() {
  pinMode(SWITCH_PIN, INPUT);
}

void loop() {
  wait();
  turnLed(0, true);
  runAround(100, 4);
  turnLed(0, false);
  warmup();
  runAround(100, 4);
  countDown();
  explode();
}
