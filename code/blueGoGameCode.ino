/* 
 Copyright (c) <2016> <ITM 492>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include <Adafruit_NeoPixel.h>
#define PIN 6 //marked D1 on GEMMA

const int buttonPin = 3;     // the number of the pushbutton pin
const int GrnLed =  12;// the number of the green LED pin

int buttonState = 0;         // variable for reading the pushbutton status
int buzzer = 13;       //buzzer pin is 11
int Time = 2400;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

int redTotal = 0;
int blueTotal = 0;

int blueScore[16];
int redScore[16];
int sine[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}; //these are the pixels in order of animation-- 36 pixels in total

int button = 9;
int lightButton = 0;
int lightot = 0;
int test = 0;
int cat = 12;
int numComparison = 0;

bool startButton = false;
bool game = false;
bool newGame = false;


void setup() {

  pinMode(10, OUTPUT);
  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(50); //adjust brightness here
  strip.show(); // Initialize all pixels to 'off'
  pinMode(9, INPUT);
  Serial.println("8x8 LED Matrix Test");

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

}

void loop() {
  do {
    if (digitalRead(3) == LOW) {
    }//end if(digitaRead(3) == LOW)

    else if (digitalRead(3) == HIGH) {
      startButton = true;
      Serial.println('D');

      while (startButton == true) {
        blueRun();
        Time -= 10;
        Serial.println(Time);


        if (Time == 0) {
          Serial.println("hey");
          newGame = true;
          startButton = false;
          Serial.println('L');
          endGame();
          newGameReset();
        }// end if (Time == 0){}

        Serial.println("here");

      }// end while loop

      Serial.println("here 2");
    }// end else if

  } while (newGame != true);
  Serial.println("here 3");
  Time = 2400;
  newGameReset();

}// end void loop()


void blueRun() {
  for (int i = 0; i <= lightot + 2; ++i) {
    strip.setPixelColor(sine[i], strip.Color(0, 0, 250));
    noColor(i);
    arraycomp(i);
    redArrayComp(i);
    lightot += 1;

    if (digitalRead(9) == HIGH) {
      strip.setPixelColor(sine[i], strip.Color(100, 100, 250));
      Serial.println('B');
      blueScore[i] = 1;
      redScore[i] = 0;
      delay(20);
      while (digitalRead(9) == HIGH) {}
    }// end if for button push

    if (Serial.read() == 'R') {
      strip.setPixelColor(sine[i], strip.Color(250, 0, 0));
      Serial.println(i);
      redScore[i] = 1;
      blueScore[i] = 0;
      delay(10);
    }

    if (lightot == 16) {
      lightot = 0;
    } // end lightot if

  } // end main for loop
}// end for Blue Void


void arraycomp(int i) {
  for (int i = 0; i <= 15; ++i) {
    if (blueScore[i] == 1) {
      strip.setPixelColor(sine[i], strip.Color(50, 50, 250));
    } // end for if statement
  } // end for for loop
  
  if (blueScore[15] == 0) {
    strip.setPixelColor(sine[15], strip.Color(0, 0, 0));
  }
  
  else if (blueScore[15] == 1) {
    strip.setPixelColor(sine[15], strip.Color(50, 50, 250));
  }
} // end for void arraycomp


void redArrayComp(int i) {
  for (int i = 0; i <= 15; ++i) {
    if (redScore[i] == 1) {
      strip.setPixelColor(sine[i], strip.Color(250, 0, 0));
    } // end for if statement
  } // end for for loop
    if (redScore[15] == 0) {
    strip.setPixelColor(sine[15], strip.Color(0, 0, 0));
  }
  
  else if (redScore[15] == 1) {
    strip.setPixelColor(sine[15], strip.Color(250, 0, 0));
  }
}


void noColor(int i) {
  strip.setPixelColor(sine[i - 1], strip.Color(0, 0, 0));
  delay(15); // controls how slow the light moves in a circle
  strip.show();
}


void endGame() {
  for (int e = 0; e <= 15; ++e) {
    redTotal += redScore[e];
    blueTotal += blueScore[e];
  }
  if (redTotal > blueTotal) {
    RedWin();
    Serial.println("Red win");
    Serial.println(redTotal);
    Serial.println(blueTotal);

    for (int i = 0; i <= 15; ++i) {
      Serial.print(i);
      Serial.print(".");
      Serial.println(redScore[i]);
      delay(1000);

    }

  }
  if (redTotal < blueTotal) {
    BlueWin();
    Serial.println("Blue win");
    Serial.println(redTotal);
    Serial.println(blueTotal);
  }

  if (redTotal == blueTotal) {
    tieGame();
    Serial.println(redTotal);
    Serial.println(blueTotal);
  }
}


void BlueWin() {
  for (int x = 0; x <= 1; ++x) {
    for (int e = 0; e <= 15; ++e) {
      strip.setPixelColor(sine[e], strip.Color(0, 0, 250));
      strip.show();
      delay(50);
    }
    for (int e = 15; e >= 0 ; --e) {
      strip.setPixelColor(sine[e], strip.Color(0, 0, 250));
      strip.show();
      delay(50);
    }
  }
  for (int x = 0; x <= 2; ++ x) {
    strip.setPixelColor(sine[0], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[1], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[2], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[3], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[4], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[5], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[6], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[7], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[8], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[9], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[10], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[11], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[12], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[13], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[14], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[15], strip.Color(0, 0, 0));
    strip.show();
    delay(170);
    strip.setPixelColor(sine[0], strip.Color(0, 0, 250));
    strip.setPixelColor(sine[1], strip.Color(0, 0, 250));
    strip.setPixelColor(sine[2], strip.Color(0, 0, 250));
    strip.setPixelColor(sine[3], strip.Color(0, 0, 250));
    strip.setPixelColor(sine[4], strip.Color(0, 0, 250));
    strip.setPixelColor(sine[5], strip.Color(0, 0, 250));
    strip.setPixelColor(sine[6], strip.Color(0, 0, 250));
    strip.setPixelColor(sine[7], strip.Color(0, 0, 250));
    strip.setPixelColor(sine[8], strip.Color(0, 0, 250));
    strip.setPixelColor(sine[9], strip.Color(0, 0, 250));
    strip.setPixelColor(sine[10], strip.Color(0, 0, 250));
    strip.setPixelColor(sine[11], strip.Color(0, 0, 250));
    strip.setPixelColor(sine[12], strip.Color(0, 0, 250));
    strip.setPixelColor(sine[13], strip.Color(0, 0, 250));
    strip.setPixelColor(sine[14], strip.Color(0, 0, 250));
    strip.setPixelColor(sine[15], strip.Color(0, 0, 250));
    strip.show();
    delay(170);
  }
}



void RedWin() {
  for (int x = 0; x <= 1; ++x) {
    for (int e = 0; e <= 16; ++e) {
      strip.setPixelColor(sine[e], strip.Color(0, 0, 250));
      strip.show();
      delay(50);
    }
    for (int e = 16; e >= 0 ; --e) {
      strip.setPixelColor(sine[e], strip.Color(0, 0, 0));
      strip.show();
      delay(50);
    }
  }
  for (int x = 0; x <= 2; ++ x) {
    strip.setPixelColor(sine[0], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[1], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[2], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[3], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[4], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[5], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[6], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[7], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[8], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[9], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[10], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[11], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[12], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[13], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[14], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[15], strip.Color(0, 0, 0));
    strip.show();
    delay(170);
    strip.setPixelColor(sine[0], strip.Color(250, 0, 0));
    strip.setPixelColor(sine[1], strip.Color(250, 0, 0));
    strip.setPixelColor(sine[2], strip.Color(250, 0, 0));
    strip.setPixelColor(sine[3], strip.Color(250, 0, 0));
    strip.setPixelColor(sine[4], strip.Color(250, 0, 0));
    strip.setPixelColor(sine[5], strip.Color(250, 0, 0));
    strip.setPixelColor(sine[6], strip.Color(250, 0, 0));
    strip.setPixelColor(sine[7], strip.Color(250, 0, 0));
    strip.setPixelColor(sine[8], strip.Color(250, 0, 0));
    strip.setPixelColor(sine[9], strip.Color(250, 0, 0));
    strip.setPixelColor(sine[10], strip.Color(250, 0, 0));
    strip.setPixelColor(sine[11], strip.Color(250, 0, 0));
    strip.setPixelColor(sine[12], strip.Color(250, 0, 0));
    strip.setPixelColor(sine[13], strip.Color(250, 0, 0));
    strip.setPixelColor(sine[14], strip.Color(250, 0, 0));
    strip.setPixelColor(sine[15], strip.Color(250, 0, 0));
    strip.show();
    delay(170);
  }
}


void tieGame() {

  for (int x = 0; x <= 5; ++ x) {
    strip.setPixelColor(sine[0], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[1], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[2], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[3], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[4], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[5], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[6], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[7], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[8], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[9], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[10], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[11], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[12], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[13], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[14], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[15], strip.Color(0, 0, 0));
    strip.show();
    delay(150);
    strip.setPixelColor(sine[0], strip.Color(250, 0, 0));
    strip.setPixelColor(sine[1], strip.Color(0, 0, 250));
    strip.setPixelColor(sine[2], strip.Color(250, 0, 0));
    strip.setPixelColor(sine[3], strip.Color(0, 0, 250));
    strip.setPixelColor(sine[4], strip.Color(250, 0, 0));
    strip.setPixelColor(sine[5], strip.Color(0, 0, 250));
    strip.setPixelColor(sine[6], strip.Color(250, 0, 0));
    strip.setPixelColor(sine[7], strip.Color(0, 0, 250));
    strip.setPixelColor(sine[8], strip.Color(250, 0, 0));
    strip.setPixelColor(sine[9], strip.Color(0, 0, 250));
    strip.setPixelColor(sine[10], strip.Color(250, 0, 0));
    strip.setPixelColor(sine[11], strip.Color(0, 0, 250));
    strip.setPixelColor(sine[12], strip.Color(250, 0, 0));
    strip.setPixelColor(sine[13], strip.Color(0, 0, 250));
    strip.setPixelColor(sine[14], strip.Color(250, 0, 0));
    strip.setPixelColor(sine[15], strip.Color(0, 0, 250));
    strip.show();
    delay(150);
  }


}

void newGameReset() {
  Serial.println("Reset");
  for (int i = 0; i <= 15; ++i) {
    redScore[i] = 0;
    blueScore[i] = 0;
    Serial.println("New Game");
  }
  redTotal = 0;
  blueTotal = 0;
}


