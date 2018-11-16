#define BRGHT_STEP 50
#define BRGHT_MAX 255
#define BRGHT_MIN 5

class Lamp
{
  public:
    Lamp(int pinR_in, int pinG_in, int pinB_in)
    {
      pinR = pinR_in;
      pinG = pinG_in;
      pinB = pinB_in;
    }
    void lampConfigure_OUTPUT()
    {
      pinMode(pinR, OUTPUT);
      pinMode(pinG, OUTPUT);
      pinMode(pinR, OUTPUT);
    }
    int pinR;
    int pinG;
    int pinB;
    int state = 0;
    int curColor = 0; //0-red 1-green 2-blue
    int brightness_R = BRGHT_MAX;
    int brightness_G = BRGHT_MIN;
    int brightness_B = BRGHT_MIN;
};

Lamp *lamp1;

void setup()
{
  lamp1 = new Lamp(11, 10, 9);
  lamp1->lampConfigure_OUTPUT();
  Serial.begin(9600);
}

void loop()
{
  char incomingByte;
  if (Serial.available() > 0)
  {
    incomingByte = Serial.read();
    switch (incomingByte)
    {
      case '1':
        switchLamp(lamp1);
        break;
      case '+':
        addBrightness(lamp1);
        break;
      case '-':
        removeBrightness(lamp1);
        break;
      case 'q':
        changeColor(lamp1);
        break;
      case 'e':
        showSpectrum(lamp1);
        break;
    }
  }
  updateLamp(lamp1);
}

void switchLamp(Lamp *lamp) {
  lamp->state = (lamp->state == 1) ? 0 : 1;
}

void addBrightness(Lamp *lamp) {
  switch (lamp->curColor)
  {
    // red
    case 0 :
      if (lamp->brightness_R >= BRGHT_MAX) {
        break;
      }
      lamp->brightness_R += BRGHT_STEP;
      break;
    // green
    case 1:
      if (lamp->brightness_G >= BRGHT_MAX) {
        break;
      }
      lamp->brightness_G += BRGHT_STEP;
      break;
    // blue
    case 2:
      if (lamp->brightness_B >= BRGHT_MAX) {
        break;
      }
      lamp->brightness_B += BRGHT_STEP;
      break;
  }
}

void removeBrightness(Lamp *lamp) {
  switch (lamp->curColor)
  {
    // red
    case 0 :
      if (lamp->brightness_R <= BRGHT_MIN) {
        break;
      }
      lamp->brightness_R -= BRGHT_STEP;
      break;
    // green
    case 1:
      if (lamp->brightness_G <= BRGHT_MIN) {
        break;
      }
      lamp->brightness_G -= BRGHT_STEP;
      break;
    // blue
    case 2:
      if (lamp->brightness_B <= BRGHT_MIN) {
        break;
      }
      lamp->brightness_B -= BRGHT_STEP;
      break;
  }
}

void changeColor(Lamp *lamp)
{
  switch (lamp->curColor)
  {
    case 0:
      lamp->curColor = 1;
      lamp->brightness_G = lamp->brightness_R;
      lamp->brightness_R = BRGHT_MIN;
      break;
    case 1:
      lamp->curColor = 2;
      lamp->brightness_B = lamp->brightness_G;
      lamp->brightness_G = BRGHT_MIN;
      break;
    case 2:
      lamp->curColor = 0;
      lamp->brightness_R = lamp->brightness_B;
      lamp->brightness_B = BRGHT_MIN;
      break;
  }
}

void showSpectrum(Lamp *lamp)
{
  int x;
  for (x = 0; x < 768; x++)
  {
    showRGB(lamp, x);
    delay(10);
  }  
  lamp->brightness_R = BRGHT_MAX;
  lamp->brightness_G = BRGHT_MIN;
  lamp->brightness_B = BRGHT_MIN;
}

void showRGB(Lamp *lamp, int color)
{
  if (color <= 255)
  {
    lamp->brightness_R = 255 - color;
    lamp->brightness_G = color;
    lamp->brightness_B = 0;
  }
  else if (color <= 511)
  {
    lamp->brightness_R = 0;
    lamp->brightness_G = 255 - (color - 256);
    lamp->brightness_B = (color - 256);
  }
  else // color >= 512
  {
    lamp->brightness_R = (color - 512);
    lamp->brightness_G = 0;
    lamp->brightness_B = 255 - (color - 512);
  }
  updateLamp(lamp);
}

void updateLamp(Lamp *lamp) {
  if (lamp->state == 1) {
    analogWrite(lamp->pinR, lamp->brightness_R);
    analogWrite(lamp->pinG, lamp->brightness_G);
    analogWrite(lamp->pinB, lamp->brightness_B);
  }
  else {
    analogWrite(lamp->pinB, LOW);
    analogWrite(lamp->pinG, LOW);
    analogWrite(lamp->pinR, LOW);
  }
}

