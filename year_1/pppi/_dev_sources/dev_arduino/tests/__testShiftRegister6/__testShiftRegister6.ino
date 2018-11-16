const int dataPin = 2;
const int latchPin = 3;
const int clockPin = 4;

int seq1[14] = {1, 2, 4, 8, 16, 32, 64, 128, 64, 32, 16, 8, 4, 2};
int seq2[14] = {128, 64, 32, 16, 8, 4, 2, 1, 2, 4, 8, 16, 32, 64};

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void loop() {

  for (int i = 0; i < 14; i++)
  {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, seq1[i]);
    shiftOut(dataPin, clockPin, MSBFIRST, seq2[i]);
    digitalWrite(latchPin, HIGH);
    delay(200);
  }
}
