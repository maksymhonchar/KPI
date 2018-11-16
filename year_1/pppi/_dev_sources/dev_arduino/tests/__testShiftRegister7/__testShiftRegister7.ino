const int dataPin = 2;
const int latchPin = 3;
const int clockPin = 4;

int seq1[] = {1, 2, 4, 8, 16, 32, 64, 128};

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void loop() {

  for (int i = 0; i < 7; i++)
  {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, seq1[i]);
    digitalWrite(latchPin, HIGH);
    delay(1000);
  }
}
