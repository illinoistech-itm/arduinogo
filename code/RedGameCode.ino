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

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

int blueScore[16];
int redScore[16];
int sine[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}; //these are the pixels in order of animation-- 36 pixels in total

int button = 9;
int lightButton = 0;
int lightot = 0;
int test = 0;
int buzzer = 13;

int redTotal = 0;
int blueTotal = 0;

bool gameOn = false;

int numComparison = 0;

int Time = 2400;

void setup() {
  pinMode(10, OUTPUT);
  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(50); //adjust brightness here
  strip.show(); // Initialize all pixels to 'off'
  pinMode(9, INPUT);

}

void loop() {
   
  if (Serial.available() > 0) {
    digitalWrite(10, HIGH);

    if (Serial.read() == 'D') {
      gameOn = true;

    }
    while (gameOn == true) {
      redRun();
      Time -= 10;
      if (Time == 0) {
        gameOn = false;
       endGame();
      }
    }
    if (gameOn == false) {
      newGameReset();    
      Time = 2400;
    }
  }
}// end void loop





void redRun() {
  if (Serial.read() == 'L') {
    gameOn = false;
  }
  for (int i = lightot; i <= lightot + 2; ++i) {
    strip.setPixelColor(sine[i], strip.Color(250, 0, 0));
    noColor(i);
    arraycomp(i);
    blueArrayComp(i);
    lightot += 1;

    if (digitalRead(9) == HIGH) {
      strip.setPixelColor(sine[i], strip.Color(250, 50, 50));
      Serial.println('R');
      redScore[i] = 1;
      blueScore[i] = 0;
      delay(20);
      while (digitalRead(9) == HIGH) {}
    }// end if for button push

    if (Serial.read() == 'B') {
      strip.setPixelColor(sine[i], strip.Color(0, 0, 250));
      Serial.println(i);
      blueScore[i] = 1;
      redScore[i] = 0;
      delay(10);
    }

    if (lightot == 16) {
      lightot = 0;
    } // end lightot if
  } // end main for loop
}// end for Red Void


void arraycomp(int i) {
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
} // end for void arraycomp


void blueArrayComp(int i) {
  for (int i = 0; i <= 15; ++i) {
    if (blueScore[i] == 1) {
      strip.setPixelColor(sine[i], strip.Color(0, 0, 250));
    } // end for if statement
  } // end for for loop

  if (blueScore[15] == 0) {
    strip.setPixelColor(sine[15], strip.Color(0, 0, 0));
  }

  else if (blueScore[15] == 1) {
    strip.setPixelColor(sine[15], strip.Color(0, 0, 250));
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

  }

  if (redTotal < blueTotal) {
    BlueWin();

  }

  if (redTotal == blueTotal) {
    tieGame();

  }
}


void BlueWin() {

  for (int x = 0; x <= 1; ++x) {
    for (int e = 0; e <= 16; ++e) {
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

    for (int e = 15; e >= 0 ; --e) {
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
    Serial.println("D");
  }
  redTotal = 0;
  blueTotal = 0;
}



void newcounttest(){
  for (int x = 0; x <= 2; ++x) {
    int r,g,b;
  if (x ==0 ) {
  r = 255; g = 0; b = 0;
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
    strip.setPixelColor(sine[0], strip.Color(r,g,b));
    strip.setPixelColor(sine[1], strip.Color(r,g,b));
    strip.setPixelColor(sine[2], strip.Color(r,g,b));
    strip.setPixelColor(sine[3], strip.Color(r,g,b));
    strip.setPixelColor(sine[4], strip.Color(r,g,b));
    strip.setPixelColor(sine[5], strip.Color(r,g,b));
    strip.setPixelColor(sine[6], strip.Color(r,g,b));
    strip.setPixelColor(sine[7], strip.Color(r,g,b));
    strip.setPixelColor(sine[8], strip.Color(r,g,b));
    strip.setPixelColor(sine[9], strip.Color(r,g,b));
    strip.setPixelColor(sine[10], strip.Color(r,g,b));
    strip.setPixelColor(sine[11], strip.Color(r,g,b));
    strip.setPixelColor(sine[12], strip.Color(r,g,b));
    strip.setPixelColor(sine[13], strip.Color(r,g,b));
    strip.setPixelColor(sine[14], strip.Color(r,g,b));
    strip.setPixelColor(sine[15], strip.Color(r,g,b));
    tone(buzzer,329,800);
    strip.show();
    delay(900);
  }

  if (x == 1){
    r = 255; g = 51; b = 0;
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
    strip.setPixelColor(sine[0], strip.Color(r,g,b));
    strip.setPixelColor(sine[1], strip.Color(r,g,b));
    strip.setPixelColor(sine[2], strip.Color(r,g,b));
    strip.setPixelColor(sine[3], strip.Color(r,g,b));
    strip.setPixelColor(sine[4], strip.Color(r,g,b));
    strip.setPixelColor(sine[5], strip.Color(r,g,b));
    strip.setPixelColor(sine[6], strip.Color(r,g,b));
    strip.setPixelColor(sine[7], strip.Color(r,g,b));
    strip.setPixelColor(sine[8], strip.Color(r,g,b));
    strip.setPixelColor(sine[9], strip.Color(r,g,b));
    strip.setPixelColor(sine[10], strip.Color(r,g,b));
    strip.setPixelColor(sine[11], strip.Color(r,g,b));
    strip.setPixelColor(sine[12], strip.Color(r,g,b));
    strip.setPixelColor(sine[13], strip.Color(r,g,b));
    strip.setPixelColor(sine[14], strip.Color(r,g,b));
    strip.setPixelColor(sine[15], strip.Color(r,g,b));
    tone(buzzer,329,800);
    strip.show();
    delay(900);
  }

  if (x == 2){
    r = 255; g = 204; b = 0;
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
    strip.setPixelColor(sine[0], strip.Color(r,g,b));
    strip.setPixelColor(sine[1], strip.Color(r,g,b));
    strip.setPixelColor(sine[2], strip.Color(r,g,b));
    strip.setPixelColor(sine[3], strip.Color(r,g,b));
    strip.setPixelColor(sine[4], strip.Color(r,g,b));
    strip.setPixelColor(sine[5], strip.Color(r,g,b));
    strip.setPixelColor(sine[6], strip.Color(r,g,b));
    strip.setPixelColor(sine[7], strip.Color(r,g,b));
    strip.setPixelColor(sine[8], strip.Color(r,g,b));
    strip.setPixelColor(sine[9], strip.Color(r,g,b));
    strip.setPixelColor(sine[10], strip.Color(r,g,b));
    strip.setPixelColor(sine[11], strip.Color(r,g,b));
    strip.setPixelColor(sine[12], strip.Color(r,g,b));
    strip.setPixelColor(sine[13], strip.Color(r,g,b));
    strip.setPixelColor(sine[14], strip.Color(r,g,b));
    strip.setPixelColor(sine[15], strip.Color(r,g,b));
    tone(buzzer,329,800);
    strip.show();
    delay(900);
  }
  }


    int r = 0, g = 255, b = 0;
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
    strip.setPixelColor(sine[0], strip.Color(r,g,b));
    strip.setPixelColor(sine[1], strip.Color(r,g,b));
    strip.setPixelColor(sine[2], strip.Color(r,g,b));
    strip.setPixelColor(sine[3], strip.Color(r,g,b));
    strip.setPixelColor(sine[4], strip.Color(r,g,b));
    strip.setPixelColor(sine[5], strip.Color(r,g,b));
    strip.setPixelColor(sine[6], strip.Color(r,g,b));
    strip.setPixelColor(sine[7], strip.Color(r,g,b));
    strip.setPixelColor(sine[8], strip.Color(r,g,b));
    strip.setPixelColor(sine[9], strip.Color(r,g,b));
    strip.setPixelColor(sine[10], strip.Color(r,g,b));
    strip.setPixelColor(sine[11], strip.Color(r,g,b));
    strip.setPixelColor(sine[12], strip.Color(r,g,b));
    strip.setPixelColor(sine[13], strip.Color(r,g,b));
    strip.setPixelColor(sine[14], strip.Color(r,g,b));
    strip.setPixelColor(sine[15], strip.Color(r,g,b));
    tone(buzzer,987,800);
    strip.show();
    delay(900);

}

