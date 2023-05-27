/***************************************************
Robot Fej forráskód
****************************************************/

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Adafruit_NeoPixel.h>


SoftwareSerial mySoftwareSerial(2, 3);  // RX, TX

DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

#define PIN_NEO_PIXEL 8
#define NUM_PIXELS 8

Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);

bool responseGiven = false;
bool questionAsked = false;
int yesButtonState = 0;
int noButtonState = 0;
// Variable to keep track of the current question
int currentQuestion = 0;

int yesButtonPin = 11;
int noButtonPin = 12;

int questionNumber = 1;
int answerNumber = 2;

void setup() {
  //led beállítás
  NeoPixel.begin();
  NeoPixel.setBrightness(50);

  pinMode(11, INPUT_PULLUP);  //jobb gomb
  pinMode(12, INPUT_PULLUP);  //bal gomb

  //beszélő beállítás
  pinMode(4, INPUT_PULLUP);

  mySoftwareSerial.begin(9600);
  Serial.begin(115200);


  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true)
      ;
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.setTimeOut(500);  //Set serial communictaion time out 500ms

  myDFPlayer.volume(30);  //Set volume value. From 0 to 30

  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);

  NeoPixel.clear();
  randomSeed(analogRead(0));
}
int buttonState_L = 0;
int buttonState_R = 0;
int prevRnd;
int rnd;
void loop() {
  while (digitalRead(yesButtonPin) == HIGH) {
    talkRandom();
  }
  while (true) {
    allPrograms();
  }
}

void allPrograms() {
  while (true) {
    rnd = random(1, 4);
    if (rnd != 1) {
      while (rnd == prevRnd) {
        rnd = random(1, 4);
      }
      prevRnd = rnd;
      break;
    }
    break;
  }
  switch (rnd) {
    case 1:
      talkRandom();
      break;
    case 2:
      vicc();
      break;
    case 3:
      game();
      break;
  }
}

void vicc() {
  int vicc = random(1, 5);
  playAnMP3(1);
  while (digitalRead(4) == 0) {
    speak();
  }
  while (digitalRead(yesButtonPin) == HIGH && digitalRead(noButtonPin) == HIGH) {
  }
  if (digitalRead(yesButtonPin) == LOW) {
    switch (vicc) {
      case 1:
        playAnMP3(5);
        while (digitalRead(4) == 0) {
          speak();
        }
        break;
      case 2:
        playAnMP3(34);
        while (digitalRead(4) == 0) {
          speak();
        }
        break;
      case 3:
        playAnMP3(35);
        while (digitalRead(4) == 0) {
          speak();
        }
        break;
      case 4:
        playAnMP3(36);
        while (digitalRead(4) == 0) {
          speak();
        }
        break;
    }

    return 0;
  } else if (digitalRead(noButtonPin) == LOW) {
    playAnMP3(2);
    while (digitalRead(4) == 0) {
      speak();
    }
    while (digitalRead(yesButtonPin) == HIGH && digitalRead(noButtonPin) == HIGH) {
    }
    if (digitalRead(yesButtonPin) == LOW) {
      playAnMP3(5);
      while (digitalRead(4) == 0) {
        speak();
      }
      return 0;

    } else if (digitalRead(noButtonPin) == LOW) {
      playAnMP3(3);
      while (digitalRead(4) == 0) {
        speak();
      }
      while (digitalRead(yesButtonPin) == HIGH && digitalRead(noButtonPin) == HIGH) {
      }
      if (digitalRead(yesButtonPin) == LOW) {
        playAnMP3(5);
        while (digitalRead(4) == 0) {
          speak();
        }
        return 0;

      } else if (digitalRead(noButtonPin) == LOW) {
        playAnMP3(4);
        while (digitalRead(4) == 0) {
          speak();
        }
        playAnMP3(5);
        while (digitalRead(4) == 0) {
          speak();
        }
        while (digitalRead(4) == 0) {
        }
        return 0;
      }
    }
  }
}

void game() {
  playAnMP3(6);
  while (digitalRead(4) == 0) {
    speak();
  }
  while (digitalRead(yesButtonPin) == HIGH && digitalRead(noButtonPin) == HIGH) {
  }

  if (digitalRead(yesButtonPin) == LOW) {
    playAnMP3(8);
    while (digitalRead(4) == 0) {
      speak();
    }
    if (digitalRead(4) == 1) {
      speak();
    }
    while (digitalRead(yesButtonPin) == HIGH && digitalRead(noButtonPin) == HIGH) {
    }
    if (digitalRead(yesButtonPin) == LOW) {
      playAnMP3(9);
      while (digitalRead(4) == 0) {
        speak();
      }
      if (digitalRead(4) == 0) {
        speak();
      }
    } else if (digitalRead(noButtonPin) == LOW) {
      playAnMP3(10);
      while (digitalRead(4) == 0) {
        speak();
      }
      if (digitalRead(4) == 0) {
        speak();
      }
    }

    ///////
    playAnMP3(11);
    while (digitalRead(4) == 0) {
      speak();
    }
    while (digitalRead(yesButtonPin) == HIGH && digitalRead(noButtonPin) == HIGH) {
    }
    if (digitalRead(yesButtonPin) == LOW) {
      playAnMP3(12);
      while (digitalRead(4) == 0) {
        speak();
      }
    } else if (digitalRead(noButtonPin) == LOW) {
      playAnMP3(13);
      while (digitalRead(4) == 0) {
        speak();
      }
    }

    ///////
    playAnMP3(14);
    while (digitalRead(4) == 0) {
      speak();
    }
    while (digitalRead(yesButtonPin) == HIGH && digitalRead(noButtonPin) == HIGH) {
    }
    if (digitalRead(yesButtonPin) == LOW) {
      playAnMP3(15);
      while (digitalRead(4) == 0) {
        speak();
      }
      playAnMP3(16);
      while (digitalRead(4) == 0) {
        speak();
      }
    } else if (digitalRead(noButtonPin) == LOW) {
      playAnMP3(17);
      while (digitalRead(4) == 0) {
        speak();
      }
    }

    ///////
    playAnMP3(18);
    while (digitalRead(4) == 0) {
      speak();
    }
    while (digitalRead(yesButtonPin) == HIGH && digitalRead(noButtonPin) == HIGH) {
    }
    if (digitalRead(yesButtonPin) == LOW) {
      playAnMP3(19);
      while (digitalRead(4) == 0) {
        speak();
      }

    } else if (digitalRead(noButtonPin) == LOW) {
      playAnMP3(20);
      while (digitalRead(4) == 0) {
        speak();
      }
    }
    playAnMP3(21);
    while (digitalRead(4) == 0) {
      speak();
    }
    return 0;
  } else if (digitalRead(noButtonPin) == LOW) {
    playAnMP3(7);
    while (digitalRead(4) == 0) {
      speak();
    }
    return 0;
  }
}

void talkRandom() {
  int rnd = random(22, 33);
  playAnMP3(rnd);
  while (digitalRead(4) == 0) {
    speak();
  }
}

void speak() {

  NeoPixel.setPixelColor(3, NeoPixel.Color(0, 255, 0));
  NeoPixel.setPixelColor(4, NeoPixel.Color(0, 255, 0));
  NeoPixel.show();
  delay(50);

  NeoPixel.setPixelColor(2, NeoPixel.Color(0, 255, 0));
  NeoPixel.setPixelColor(5, NeoPixel.Color(0, 255, 0));
  NeoPixel.show();
  delay(50);


  NeoPixel.setPixelColor(1, NeoPixel.Color(0, 255, 0));
  NeoPixel.setPixelColor(6, NeoPixel.Color(0, 255, 0));
  NeoPixel.show();
  delay(50);

  NeoPixel.setPixelColor(0, NeoPixel.Color(0, 255, 0));
  NeoPixel.setPixelColor(7, NeoPixel.Color(0, 255, 0));
  NeoPixel.show();
  delay(50);


  ///////////////////////

  NeoPixel.setPixelColor(0, NeoPixel.Color(0, 0, 0));
  NeoPixel.setPixelColor(7, NeoPixel.Color(0, 0, 0));
  NeoPixel.show();
  delay(50);

  NeoPixel.setPixelColor(1, NeoPixel.Color(0, 0, 0));
  NeoPixel.setPixelColor(6, NeoPixel.Color(0, 0, 0));
  NeoPixel.show();
  delay(50);

  NeoPixel.setPixelColor(2, NeoPixel.Color(0, 0, 0));
  NeoPixel.setPixelColor(5, NeoPixel.Color(0, 0, 0));
  NeoPixel.show();
  delay(50);

  NeoPixel.setPixelColor(3, NeoPixel.Color(0, 0, 0));
  NeoPixel.setPixelColor(4, NeoPixel.Color(0, 0, 0));
  NeoPixel.show();
  delay(50);
}

void playAnMP3(int trackNumber) {
  if (digitalRead(4) == 1) {
    myDFPlayer.play(trackNumber);
  }
  delay(500);
}


void printDetail(uint8_t type, int value) {
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}