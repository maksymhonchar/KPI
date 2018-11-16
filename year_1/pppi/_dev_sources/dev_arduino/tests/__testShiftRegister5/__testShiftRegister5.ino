const int dataPin = 2;
const int latchPin = 3;
const int clockPin = 4;

int byte1 = 0; // SR #1
int byte2 = 0; // SR #2

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void loop() {
  for(byte2 = 0; byte2 < 256; byte2++)
  {
    for(byte1 = 0; byte1 < 256; byte1++)
    {
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, byte1);
      shiftOut(dataPin, clockPin, MSBFIRST, byte2);
      digitalWrite(latchPin, HIGH);
      delay(50);
    }
  }

}
