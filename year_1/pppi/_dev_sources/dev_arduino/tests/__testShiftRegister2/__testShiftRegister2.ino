int latchpin = 8;
int clockpin = 12;
int datapin = 11;

void setup() {
  pinMode(latchpin, OUTPUT);
  pinMode(clockpin, OUTPUT);
  pinMode(datapin, OUTPUT);
}

void loop() {
  for(int numberToDisplay = 0; numberToDisplay < 255; numberToDisplay++)
  {
    digitalWrite(latchpin, LOW);
    shiftOut(datapin, clockpin, MSBFIRST, numberToDisplay);
    digitalWrite(latchpin, HIGH);
    delay(500);
  }
}
