int datapin = 2;
int latchpin = 4;
int clockpin = 3;

byte data = 0;

void setup() {
  pinMode(datapin, OUTPUT);
  pinMode(latchpin, OUTPUT);
  pinMode(clockpin, OUTPUT);
}

void loop() {
  testFunc();
}

void shiftWrite(int desiredPin, boolean desiredState)
{
  bitWrite(data, desiredPin, desiredState);
  shiftOut(datapin, clockpin, MSBFIRST, data);
  digitalWrite(latchpin, HIGH);
  digitalWrite(latchpin, LOW);
}

void testFunc()
{
  for(int i = 0; i < 8; i++)
  {
    shiftWrite(i, HIGH);
    delay(500);
    shiftWrite(i,LOW);
  }
}

