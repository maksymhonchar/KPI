int latchpin = 8;
int clockpin = 12;
int datapin = 11;

void setup() {
  pinMode(latchpin, OUTPUT);
  pinMode(clockpin, OUTPUT);
  pinMode(datapin, OUTPUT);
}

void loop() {
  for (int i = 0; i <= 255; i++)
  {
    digitalWrite(latchpin, LOW);
    // first shift register
    shiftOut(datapin, clockpin, MSBFIRST, i);
    // second shift register
    shiftOut(datapin, clockpin, MSBFIRST, 255 - i);
    digitalWrite(latchpin, HIGH);
    delay(300);
  }
}
