#include <SPI.h> 
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 15;
int numberOfHorizontalDisplays = 1;
int numberOfVerticalDisplays = 1;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

int wait = 100;
int spacer = 1;
int width = 5 + spacer;

void setupMatrix() {
    matrix.setIntensity(15);
    matrix.setRotation(4);
    matrix.fillScreen(LOW);
    matrix.write();
}

void drawPattern(const byte pattern[8]) {
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      bool pixelState = bitRead(pattern[y], 7 - x);
      matrix.drawPixel(x, y, pixelState);
    }
  }
  matrix.write();
}

void drawHeart() {
  byte heart[8] = {
    B01100110,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B01111110,
    B00111100,
    B00011000
  };
  drawPattern(heart);
}

void drawSSmile() {
  byte sad_smile[8] = {
    B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10011001,
    B10100101,
    B01000010,
    B00111100
  };
  drawPattern(sad_smile);
}

void drawHSmile() {
  byte happy_smile[8] = {
    B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100
  };
  drawPattern(happy_smile);
}

void exclamationMark() {
  byte E_mark[8] = {
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00000000,
    B00011000
  };
  drawPattern(E_mark);
}

void questionMark() {
  byte Q_mark[8] = {
    B00111100,
    B01111110,
    B01100110,
    B01100110,
    B00001100,
    B00011000,
    B00000000,
    B00011000
  };
  drawPattern(Q_mark);
}


void drawCat() {
  byte cat[8] = {
    B10001000,
    B11111000,
    B10101000,
    B01110001,
    B00100001,
    B01111001,
    B01111101,
    B10111110
  };
  drawPattern(cat);
}

void drawDog() {
  byte dog[8] = {
    B00100000,
    B11100000,
    B11100001,
    B00111110,
    B00111110,
    B00111110,
    B00100010,
    B01100110
  };
  drawPattern(dog);
}

void ScrollText (String text){
    for ( int i = 0 ; i < width * text.length() + matrix.width() - 1 - spacer; i++ ) {
    matrix.fillScreen(LOW);
    int letter = i / width;
    int x = (matrix.width() - 1) - i % width;
    int y = (matrix.height() - 8) / 2;
 
    while ( x + width - spacer >= 0 && letter >= 0 ) {
      if ( letter < text.length() ) {
        matrix.drawChar(x, y, text[letter], HIGH, LOW, 1);
      }
      letter--;
      x -= width;
    }
    matrix.write();
    delay(wait);
  }
}

void DisplayTime(){
  setenv("TZ", "UTC-8", 1);
  tzset();
  time_t now;
  struct tm *timeinfo;
  time(&now);
  timeinfo = localtime(&now);
  char timeStr[9];
  strftime(timeStr, sizeof(timeStr), "%H:%M:%S", timeinfo);
  ScrollText(timeStr);
}
