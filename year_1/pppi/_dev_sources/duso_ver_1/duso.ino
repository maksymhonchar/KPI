/*
  Fields to represent state of lamp.
*/
#define ON 1
#define OFF 0

/*
  Field to represent number of lamps on breadboard.
*/
#define LAMPS_MAX_COUNT 8

/*
  Field to control brightness changing.
*/
#define BRGHT_MIN 5
#define BRGHT_MAX 255
#define BRGHT_STEP 50

/*
  Field to control delay() time.
*/
#define SLEEP_TIME 75

/*
  Fields for shift register to control all lamps.
  On breadboard, from left to right: Data->Latch->Clock.
*/
#define LATCHPIN 8
#define DATAPIN 11
#define CLOCKPIN 12

/*
  Field to control brightness.
*/
#define BRGHT_PIN 3

/*
  Class to represent lamp structure.
*/
class Lamp
{
  public:
    /*
      Class constructor.
      Sets indexes, global values, current values and shiftRegister id.
    */
    Lamp(int pinR_in, int pinG_in, int pinB_in,
         int valueR_in, int valueG_in, int valueB_in,
         int shiftRegister_in)
    {
      this->indexR = pinR_in;
      this->indexG = pinG_in;
      this->indexB = pinB_in;
      this->valueR = valueR_in;
      this->valueG = valueG_in;
      this->valueB = valueB_in;
      this->shiftRegister = shiftRegister_in;
    }

    /*
      {0,1,2,3,4,5,6,7}
      Index means input to shift register.
    */
    int indexR;
    int indexG;
    int indexB;

    /*
      {1,2,4,8,16,32,64,128}
      Value means bit representation. Depends on shift register.
      We need this to write certain byte to shift register data.
    */
    int valueR;
    int valueG;
    int valueB;

    /*
      1,2,3 - first, second or third register.
      4 - first and second registers.
      5 - second and third registers.
    */
    int shiftRegister;

    /*
      Lamp state - ON (1) or OFF (0).
    */
    int state = OFF;

    /*
      0 - red; 1 - green; 2 - blue.
    */
    int curColor = 0;
};

Lamp *lampSet[LAMPS_MAX_COUNT] = {
  // First shift registor.
  new Lamp(0, 1, 2, 1, 2, 4, 1),
  new Lamp(3, 4, 5, 8, 16, 32, 1),
  // First & second shift registor.
  new Lamp(6, 7, 0, 64, 128, 1, 4),
  // Second shift registor.
  new Lamp(1, 2, 3, 2, 4, 8, 2),
  new Lamp(4, 5, 6, 16, 32, 64, 2),
  // Second & third shift registors.
  new Lamp(7, 0, 1, 128, 1, 2, 5),
  // Third shift registor.
  new Lamp(2, 3, 4, 4, 8, 16, 3),
  new Lamp(5, 6, 7, 32, 64, 128, 3)
};

byte curBrightness = BRGHT_MAX;

char incomingByte = 0;

/*
   Current lamps state.
*/
int srdata1[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int srdata2[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int srdata3[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void setup()
{
  pinMode(DATAPIN, OUTPUT);
  pinMode(CLOCKPIN, OUTPUT);
  pinMode(LATCHPIN, OUTPUT);
  pinMode(BRGHT_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available() > 0)
  {
    incomingByte = Serial.read();
    if ((incomingByte >= '1') && (incomingByte <= '6'))
    {
      lamp_changeBrightness(incomingByte - '0');
      Serial.print("Number received: ");
      Serial.println(incomingByte);
    }
    else
    {
      switch (incomingByte)
      {
        case 'q':
          lamp_switchLamp(lampSet[0]);
          break;
        case 'w':
          lamp_switchLamp(lampSet[1]);
          break;
        case 'e':
          lamp_switchLamp(lampSet[2]);
          break;
        case 'r':
          lamp_switchLamp(lampSet[3]);
          break;
        case 't':
          lamp_switchLamp(lampSet[4]);
          break;
        case 'y':
          lamp_switchLamp(lampSet[5]);
          break;
        case 'u':
          lamp_switchLamp(lampSet[6]);
          break;
        case 'i':
          lamp_switchLamp(lampSet[7]);
          break;
        case 'a':
          lamp_changeColor(lampSet[0]);
          break;
        case 's':
          lamp_changeColor(lampSet[1]);
          break;
        case 'd':
          lamp_changeColor(lampSet[2]);
          break;
        case 'f':
          lamp_changeColor(lampSet[3]);
          break;
        case 'g':
          lamp_changeColor(lampSet[4]);
          break;
        case 'h':
          lamp_changeColor(lampSet[5]);
          break;
        case 'j':
          lamp_changeColor(lampSet[6]);
          break;
        case 'k':
          lamp_changeColor(lampSet[7]);
          break;
        case 'o':
          for (int i = 0; i < LAMPS_MAX_COUNT; i++)
          {
            lamp_changeColor(lampSet[i]);
          }
          break;
        case 'p':
          for (int i = 0; i < LAMPS_MAX_COUNT; i++)
          {
            lamp_switchLamp(lampSet[i]);
          }
          break;
        case 'z':
          while (1) {
            char modeByte = Serial.read();
            if (modeByte == 'z') {
              for (int i = 0; i < 3; i++) {
                pingPong();
              }
              break;
            }
            else if (modeByte == 'x') {
              for (int i = 0; i < 10; i++) {
                newYear();
              }
              break;
            }
            else if (modeByte == 'c') {
              for (int i = 0; i < 2; i++) {
                chaser();
                delay(1000);
              }
              break;
            }
            else if (modeByte == 'v') {
              sorcerer();
              break;
            }
          }
          break;
      }
    }
  }
  // Update data in shift registers.
  lamp_updateLamps(srDataSum(srdata1),
                   srDataSum(srdata2),
                   srDataSum(srdata3)
                  );
}

void lamp_switchLamp(Lamp *curLamp)
{
  // If state was ON, turn lamp off.
  if (curLamp->state == ON)
  {
    switch (curLamp->shiftRegister)
    {
      case 1:
        srdata1[curLamp->indexR] = 0;
        srdata1[curLamp->indexG] = 0;
        srdata1[curLamp->indexB] = 0;
        break;
      case 2:
        srdata2[curLamp->indexR] = 0;
        srdata2[curLamp->indexG] = 0;
        srdata2[curLamp->indexB] = 0;
        break;
      case 3:
        srdata3[curLamp->indexR] = 0;
        srdata3[curLamp->indexG] = 0;
        srdata3[curLamp->indexB] = 0;
        break;
      case 4:
        srdata1[curLamp->indexR] = 0;
        srdata1[curLamp->indexG] = 0;
        srdata2[curLamp->indexB] = 0;
        break;
      case 5:
        srdata2[curLamp->indexR] = 0;
        srdata3[curLamp->indexG] = 0;
        srdata3[curLamp->indexB] = 0;
        break;
    }
  }
  // If state was OFF, turn lamp ON!
  else
  {
    switch (curLamp->curColor)
    {
      // If current color was red:
      case 0:
        switch (curLamp->shiftRegister)
        {
          case 1:
            srdata1[curLamp->indexR] = curLamp->valueR;
            srdata1[curLamp->indexG] = 0;
            srdata1[curLamp->indexB] = 0;
            break;
          case 2:
            srdata2[curLamp->indexR] = curLamp->valueR;
            srdata2[curLamp->indexG] = 0;
            srdata2[curLamp->indexB] = 0;
            break;
          case 3:
            srdata3[curLamp->indexR] = curLamp->valueR;
            srdata3[curLamp->indexG] = 0;
            srdata3[curLamp->indexB] = 0;
            break;
          case 4:
            srdata1[curLamp->indexR] = curLamp->valueR;
            srdata1[curLamp->indexG] = 0;
            srdata2[curLamp->indexB] = 0;
            break;
          case 5:
            srdata2[curLamp->indexR] = curLamp->valueR;
            srdata3[curLamp->indexG] = 0;
            srdata3[curLamp->indexB] = 0;
            break;
        }
        break;
      // If current color was green:
      case 1:
        switch (curLamp->shiftRegister)
        {
          case 1:
            srdata1[curLamp->indexR] = 0;
            srdata1[curLamp->indexG] = curLamp->valueG;
            srdata1[curLamp->indexB] = 0;
            break;
          case 2:
            srdata2[curLamp->indexR] = 0;
            srdata2[curLamp->indexG] = curLamp->valueG;
            srdata2[curLamp->indexB] = 0;
            break;
          case 3:
            srdata3[curLamp->indexR] = 0;
            srdata3[curLamp->indexG] = curLamp->valueG;
            srdata3[curLamp->indexB] = 0;
            break;
          case 4:
            srdata1[curLamp->indexR] = 0;
            srdata1[curLamp->indexG] = curLamp->valueG;
            srdata2[curLamp->indexB] = 0;
            break;
          case 5:
            srdata2[curLamp->indexR] = 0;
            srdata3[curLamp->indexG] = curLamp->valueG;
            srdata3[curLamp->indexB] = 0;
            break;
        }
        break;
      // If curColor was blue.
      case 2:
        switch (curLamp->shiftRegister)
        {
          case 1:
            srdata1[curLamp->indexR] = 0;
            srdata1[curLamp->indexG] = 0;
            srdata1[curLamp->indexB] = curLamp->valueB;
            break;
          case 2:
            srdata2[curLamp->indexR] = 0;
            srdata2[curLamp->indexG] = 0;
            srdata2[curLamp->indexB] = curLamp->valueB;
            break;
          case 3:
            srdata3[curLamp->indexR] = 0;
            srdata3[curLamp->indexG] = 0;
            srdata3[curLamp->indexB] = curLamp->valueB;
            break;
          case 4:
            srdata1[curLamp->indexR] = 0;
            srdata1[curLamp->indexG] = 0;
            srdata2[curLamp->indexB] = curLamp->valueB;
            break;
          case 5:
            srdata2[curLamp->indexR] = 0;
            srdata3[curLamp->indexG] = 0;
            srdata3[curLamp->indexB] = curLamp->valueB;
            break;
        }
        break;
    }
  }
  curLamp->state = (curLamp->state == ON) ? OFF : ON;
}

void lamp_changeBrightness(int num)
{
    curBrightness = 5 + (num - 1) * 50;
    Serial.print("Calculated: ");
    Serial.println(curBrightness);
}

void lamp_changeColor(Lamp *curLamp)
{
  if (curLamp->state == OFF)
    return;
  switch (curLamp->curColor)
  {
    // If current color was red.
    case 0:
      curLamp->curColor = 1;
      switch (curLamp->shiftRegister)
      {
        // If current color was blue.
        case 1:
          srdata1[curLamp->indexR] = 0;
          srdata1[curLamp->indexG] = curLamp->valueG;
          srdata1[curLamp->indexB] = 0;
          break;
        case 2:
          srdata2[curLamp->indexR] = 0;
          srdata2[curLamp->indexG] = curLamp->valueG;
          srdata2[curLamp->indexB] = 0;
          break;
        case 3:
          srdata3[curLamp->indexR] = 0;
          srdata3[curLamp->indexG] = curLamp->valueG;
          srdata3[curLamp->indexB] = 0;
          break;
        case 4:
          srdata1[curLamp->indexR] = 0;
          srdata1[curLamp->indexG] = curLamp->valueG;
          srdata2[curLamp->indexB] = 0;
          break;
        case 5:
          srdata2[curLamp->indexR] = 0;
          srdata3[curLamp->indexG] = curLamp->valueG;
          srdata3[curLamp->indexB] = 0;
          break;
      }
      break;
    // If current color was green.
    case 1:
      curLamp->curColor = 2;
      switch (curLamp->shiftRegister)
      {
        case 1:
          srdata1[curLamp->indexR] = 0;
          srdata1[curLamp->indexG] = 0;
          srdata1[curLamp->indexB] = curLamp->valueB;
          break;
        case 2:
          srdata2[curLamp->indexR] = 0;
          srdata2[curLamp->indexG] = 0;
          srdata2[curLamp->indexB] = curLamp->valueB;
          break;
        case 3:
          srdata3[curLamp->indexR] = 0;
          srdata3[curLamp->indexG] = 0;
          srdata3[curLamp->indexB] = curLamp->valueB;
          break;
        case 4:
          srdata1[curLamp->indexR] = 0;
          srdata1[curLamp->indexG] = 0;
          srdata2[curLamp->indexB] = curLamp->valueB;
          break;
        case 5:
          srdata2[curLamp->indexR] = 0;
          srdata3[curLamp->indexG] = 0;
          srdata3[curLamp->indexB] = curLamp->valueB;
          break;
      }
      break;
    // If current color was blue.
    case 2:
      curLamp->curColor = 0;
      switch (curLamp->shiftRegister)
      {
        case 1:
          srdata1[curLamp->indexG] = 0;
          srdata1[curLamp->indexB] = 0;
          srdata1[curLamp->indexR] = curLamp->valueR;
          break;
        case 2:
          srdata2[curLamp->indexG] = 0;
          srdata2[curLamp->indexB] = 0;
          srdata2[curLamp->indexR] = curLamp->valueR;
          break;
        case 3:
          srdata3[curLamp->indexG] = 0;
          srdata3[curLamp->indexB] = 0;
          srdata3[curLamp->indexR] = curLamp->valueR;
          break;
        case 4:
          srdata1[curLamp->indexG] = 0;
          srdata2[curLamp->indexB] = 0;
          srdata1[curLamp->indexR] = curLamp->valueR;
          break;
        case 5:
          srdata3[curLamp->indexG] = 0;
          srdata3[curLamp->indexB] = 0;
          srdata2[curLamp->indexR] = curLamp->valueR;
          break;
      }
      break;
  }
}

void lamp_updateLamps(int srdata1_sum, int srdata2_sum, int srdata3_sum)
{
  // Update data in shift register.
  digitalWrite(LATCHPIN, LOW);
  shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, srdata3_sum);
  shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, srdata2_sum);
  shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, srdata1_sum);
  digitalWrite(LATCHPIN, HIGH);
  // Update lampSet brightness.
  analogWrite(BRGHT_PIN, 255 - curBrightness);
}

int srDataSum(int *srData)
{
  int out = 0;
  for (int i = 0; i < 8; i++)
  {
    out += srData[i];
  }
  return (out);
}

void pingPong()
{
  int redSR[] = {1, 2, 4, 8, 16, 32, 64, 128};

  // RED RED RED
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(LATCHPIN, LOW);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, 0);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, 0);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, redSR[i]);
    digitalWrite(LATCHPIN, HIGH);
    delay(50);
  }
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(LATCHPIN, LOW);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, 0);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, redSR[i]);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, 0);
    digitalWrite(LATCHPIN, HIGH);
    delay(50);
  }
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(LATCHPIN, LOW);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, redSR[i]);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, 0);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, 0);
    digitalWrite(LATCHPIN, HIGH);
    delay(50);
  }
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(LATCHPIN, LOW);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, redSR[7 - i]);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, 0);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, 0);
    digitalWrite(LATCHPIN, HIGH);
    delay(50);
  }
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(LATCHPIN, LOW);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, 0);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, redSR[7 - i]);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, 0);
    digitalWrite(LATCHPIN, HIGH);
    delay(50);
  }
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(LATCHPIN, LOW);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, 0);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, 0);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, redSR[7 - i]);
    digitalWrite(LATCHPIN, HIGH);
    delay(50);
  }
}

//TESTING FUNCTION TO SEE BYTES IN SHIFT REGISTER! (e.g. printBytes(allSR[j]))
void printBytes(int byte[8]) {
  for (int i = 0; i < 8; i++) {
    Serial.print(byte[i]);
    Serial.print(" ");
  }
  Serial.println("");
}

//NEW YEAR animation func
void newYear() {
  int allSR[3][8] = {
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 }
  };
  int rgb;

  for (int i = 0; i < 3; i++) {
    rgb = i;
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 8; k++) {
        if ((j * 8 + k) % 3 == rgb && ((j * 8 + k) / 3 + i) % 3 == rgb) {
          allSR[j][k] = pow(2, k);
          if (k >= 2) {
            allSR[j][k] += 1;
          }
          rgb++;
          rgb = rgb % 3;
        }
        else {
          allSR[j][k] = 0;
        }
      }
    }
    digitalWrite(LATCHPIN, LOW);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, srDataSum(allSR[2]));
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, srDataSum(allSR[1]));
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, srDataSum(allSR[0]));
    digitalWrite(LATCHPIN, HIGH);
    delay(100);
  }
}

//CHASER animation func
void chaser() {
  int allSR[3][8] = {
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 }
  };
  int k;

  for (int i = 0; i < 3; i++) {
    k = i;
    for (int j = 0; j < 3; j++) {
      for (; k < 8; k += 3) {
        allSR[j][k] = pow(2, k);
        if (k >= 2) {
          allSR[j][k] += 1;
        }
        digitalWrite(LATCHPIN, LOW);
        shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, srDataSum(allSR[2]));
        shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, srDataSum(allSR[1]));
        shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, srDataSum(allSR[0]));
        digitalWrite(LATCHPIN, HIGH);
        delay(50);
      }
      k = k % 8;
    }
    k = i;
    for (int j = 0; j < 3; j++) {
      for (; k < 8; k += 3) {
        allSR[j][k] = 0;
        digitalWrite(LATCHPIN, LOW);
        shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, srDataSum(allSR[2]));
        shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, srDataSum(allSR[1]));
        shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, srDataSum(allSR[0]));
        digitalWrite(LATCHPIN, HIGH);
        delay(50);
      }
      k = k % 8;
    }
    delay(300);
  }
}

//ADDITIONAL FUNCTION FOR X-Ray Dog - Sorcerer (remix) animation func
void blinkAndSleep(int milliseconds) {
  delay(milliseconds - SLEEP_TIME);
  for (int i = 0; i < LAMPS_MAX_COUNT; i++) {
    lamp_switchLamp(lampSet[i]);
  }
  lamp_updateLamps(srDataSum(srdata1),
                   srDataSum(srdata2),
                   srDataSum(srdata3)
                  );
  delay(SLEEP_TIME);
  for (int i = 0; i < LAMPS_MAX_COUNT; i++) {
    lamp_switchLamp(lampSet[i]);
  }
  lamp_updateLamps(srDataSum(srdata1),
                   srDataSum(srdata2),
                   srDataSum(srdata3)
                  );
}

//X-Ray Dog - Sorcerer (remix) animation func
//ATTENTION: LAMPS MUST BE OFF BEFORE THE ANIMATION WILL START!
void sorcerer() {
  //array with delay() time for the main part
  int delayTime[] = { 346, 2662, 380, 1187, 352, 1140, 369, 2819, 349, 1196,
                      360, 1123, 351, 2788, 337, 1213, 352, 1163, 360, 2779,
                      331, 1182, 374, 1180, 360, 2769, 337, 1159, 362, 4309,
                      372, 394, 373, 1162, 358, 1175, 362, 1176, 191, 195,
                      1130, 353, 1210, 357, 1213, 353, 1187, 190, 203, 1130,
                      364, 1191, 384, 1202, 348, 1168, 180, 183, 1139, 387,
                      1231, 355, 1141, 415, 1095, 195, 195, 1996, 376, 399,
                      403, 1134, 385, 1177, 361, 1174, 186, 184, 1139, 337,
                      1206, 343, 1214, 344, 1192, 197, 208, 1150, 350, 1192,
                      363, 1200, 342, 1153, 195, 225, 456, 199, 189, 179, //456->481
                      193, 420, 182, 184, 175, 125, 1000, 221, 197, 180, //125->221,1000->1100
                      213, 394, 203, 189, 232, 1249, 211, 195, 182, 216,
                      417, 190, 199, 241, 1267, 198, 190, 188, 218, 387,
                      192, 176, 187, 187, 409
                    };
  //for the ending
  int allSR[3][8] = {
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 }
  };
  int k = 0;
  //

  //first initial blink without delay minus SLEEP_TIME
  blinkAndSleep(653 + 75);
  //

  //other blinks (135 times)
  for (int i = 0; i < 135; i++) {
    blinkAndSleep(delayTime[i]);
  }
  //

  //after the last animation: turn on simplified chaser func
  for (int j = 0; j < 3; j++) {
    for (; k < 8; k += 3) {
      allSR[j][k] = pow(2, k);
      if (k >= 2) {
        allSR[j][k] += 1;
      }
      digitalWrite(LATCHPIN, LOW);
      shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, srDataSum(allSR[2]));
      shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, srDataSum(allSR[1]));
      shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, srDataSum(allSR[0]));
      digitalWrite(LATCHPIN, HIGH);
      delay(50);
    }
    k = k % 8;
  }
  for (int j = 0; j < 3; j++) {
    for (; k < 8; k += 3) {
      allSR[j][k] = 0;
      digitalWrite(LATCHPIN, LOW);
      shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, srDataSum(allSR[2]));
      shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, srDataSum(allSR[1]));
      shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, srDataSum(allSR[0]));
      digitalWrite(LATCHPIN, HIGH);
      delay(50);
    }
    k = k % 8;
  }
  //
}
