#include <Adafruit_NeoPixel.h>

int ANIMDELAY = 100;   // animation delay, deafault value is 100
int INTENSITYMIN = 0;  // minimum brightness, valid range [0,15]
int INTENSITYMAX = 8;  // maximum brightness, valid range [0,15]

int CLK_PIN_L = 2;
int CS_PIN_L = 3;
int DIN_PIN_L = 4;

int CLK_PIN_R = 5;
int CS_PIN_R = 6;
int DIN_PIN_R = 7;


// MAX7219 registers
byte MAXREG_DECODEMODE = 0x09;
byte MAXREG_INTENSITY = 0x0a;
byte MAXREG_SCANLIMIT = 0x0b;
byte MAXREG_SHUTDOWN = 0x0c;
byte MAXREG_DISPTEST = 0x0f;

#define PIN_NEO_PIXEL 4
#define NUM_PIXELS 8

Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);

const unsigned char open[] = {
  B00111100,
  B01111110,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B01111110,
  B00111100
};

const unsigned char mid_closed[] = {
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000
};

const unsigned char closed[] = {
  B00010000,
  B00010000,
  B00010000,
  B00010000,
  B00010000,
  B00010000,
  B00010000,
  B00010000
};


void setup() {
  //led beállítás
  NeoPixel.begin();
  NeoPixel.setBrightness(50);

  pinMode(DIN_PIN_L, OUTPUT);
  pinMode(CLK_PIN_L, OUTPUT);
  pinMode(CS_PIN_L, OUTPUT);

  pinMode(DIN_PIN_R, OUTPUT);
  pinMode(CLK_PIN_R, OUTPUT);
  pinMode(CS_PIN_R, OUTPUT);

  // initialization of the MAX7219
  setRegistry(MAXREG_SCANLIMIT, 0x07, CS_PIN_L, CLK_PIN_L, DIN_PIN_L);
  setRegistry(MAXREG_DECODEMODE, 0x00, CS_PIN_L, CLK_PIN_L, DIN_PIN_L);
  setRegistry(MAXREG_SHUTDOWN, 0x01, CS_PIN_L, CLK_PIN_L, DIN_PIN_L);
  setRegistry(MAXREG_DISPTEST, 0x00, CS_PIN_L, CLK_PIN_L, DIN_PIN_L);
  setRegistry(MAXREG_INTENSITY, 0x0f & INTENSITYMIN, CS_PIN_L, CLK_PIN_L, DIN_PIN_L);

  setRegistry(MAXREG_SCANLIMIT, 0x07, CS_PIN_R, CLK_PIN_R, DIN_PIN_R);
  setRegistry(MAXREG_DECODEMODE, 0x00, CS_PIN_R, CLK_PIN_R, DIN_PIN_R);
  setRegistry(MAXREG_SHUTDOWN, 0x01, CS_PIN_R, CLK_PIN_R, DIN_PIN_R);
  setRegistry(MAXREG_DISPTEST, 0x00, CS_PIN_R, CLK_PIN_R, DIN_PIN_R);
  setRegistry(MAXREG_INTENSITY, 0x0f & INTENSITYMIN, CS_PIN_R, CLK_PIN_R, DIN_PIN_R);

  NeoPixel.clear();
}


void loop() {
  int rnd = random(1, 5);
  draw(open, CS_PIN_L, CLK_PIN_L, DIN_PIN_L);
  draw(open, CS_PIN_R, CLK_PIN_R, DIN_PIN_R);
  delay(rnd * 1000);
  draw(closed, CS_PIN_L, CLK_PIN_L, DIN_PIN_L);
  draw(closed, CS_PIN_R, CLK_PIN_R, DIN_PIN_R);
  delay(100);
}

void speak() {

  NeoPixel.setPixelColor(3, NeoPixel.Color(0, 255, 0));
  NeoPixel.setPixelColor(4, NeoPixel.Color(0, 255, 0));
  NeoPixel.show();
  delay(100);

  NeoPixel.setPixelColor(2, NeoPixel.Color(0, 255, 0));
  NeoPixel.setPixelColor(5, NeoPixel.Color(0, 255, 0));
  NeoPixel.show();
  delay(100);


  NeoPixel.setPixelColor(1, NeoPixel.Color(0, 255, 0));
  NeoPixel.setPixelColor(6, NeoPixel.Color(0, 255, 0));
  NeoPixel.show();
  delay(100);

  NeoPixel.setPixelColor(0, NeoPixel.Color(0, 255, 0));
  NeoPixel.setPixelColor(7, NeoPixel.Color(0, 255, 0));
  NeoPixel.show();
  delay(100);

  NeoPixel.clear();
  NeoPixel.show();
}

void draw(const unsigned char form[], int CS_PIN, int CLK_PIN, int DIN_PIN) {
  setRegistry(1, form[0], CS_PIN, CLK_PIN, DIN_PIN);
  setRegistry(2, form[1], CS_PIN, CLK_PIN, DIN_PIN);
  setRegistry(3, form[2], CS_PIN, CLK_PIN, DIN_PIN);
  setRegistry(4, form[3], CS_PIN, CLK_PIN, DIN_PIN);
  setRegistry(5, form[4], CS_PIN, CLK_PIN, DIN_PIN);
  setRegistry(6, form[5], CS_PIN, CLK_PIN, DIN_PIN);
  setRegistry(7, form[6], CS_PIN, CLK_PIN, DIN_PIN);
  setRegistry(8, form[7], CS_PIN, CLK_PIN, DIN_PIN);
  // second beat
  setRegistry(MAXREG_INTENSITY, 0x0f & INTENSITYMAX, CS_PIN, CLK_PIN, DIN_PIN);
}

void setRegistry(byte reg, byte value, int CS_PIN, int CLK_PIN, int DIN_PIN) {
  digitalWrite(CS_PIN, LOW);

  putByte(reg, CLK_PIN, DIN_PIN);    // specify register
  putByte(value, CLK_PIN, DIN_PIN);  // send data

  digitalWrite(CS_PIN, LOW);
  digitalWrite(CS_PIN, HIGH);
}

void putByte(byte data, int CLK_PIN, int DIN_PIN) {
  byte i = 8;
  byte mask;
  while (i > 0) {
    mask = 0x01 << (i - 1);         // get bitmask
    digitalWrite(CLK_PIN, LOW);     // tick
    if (data & mask)                // choose bit
      digitalWrite(DIN_PIN, HIGH);  // send 1
    else
      digitalWrite(DIN_PIN, LOW);  // send 0
    digitalWrite(CLK_PIN, HIGH);   // tock
    --i;                           // move to lesser bit
  }
}