#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define LED_PIN    6        // Pin 6 on 32u4 Feathers

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 32        // 8x4 grid on Neopixel Featherwing

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

uint32_t green;
uint32_t yellow;
uint32_t red;
uint32_t off;

int row0;
int row1;
int row2;
int row3;

void setup() {
  Serial.begin(9600);
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(3);

  green = strip.Color(0, 64, 0);
  yellow = strip.Color(64, 64, 0);
  red = strip.Color(64, 0, 0);
  off = strip.Color(0,0,0);

  row0 = row1 = row2 = row3 = 50;
}

void loop() {
  row0 = nextVal(row0);
  row1 = nextVal(row1);
  row2 = nextVal(row2);
  row3 = nextVal(row3);
  
  setRow( 0, row0);
  setRow( 8, row1);
  setRow(16, row2);
  setRow(24, row3);
}

int nextVal(int val) {
 return min(max(val + random(-5, 6), 0), 100); 
}

void setRow(int start, int val) {
  val = (val * 8)/100;
  if (val <= 0)
    strip.fill(off, start, 8);
  else if(val < 5)
    strip.fill(green, start, val);
  else if (val < 6)
    strip.fill(yellow, start, val);
  else
    strip.fill(red, start, val);
    
  if(val < 8)
    strip.fill(off, (start + val), (8 - val));
    
  strip.show();
}
