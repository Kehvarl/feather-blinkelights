#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define LED_PIN    6        // Pin 6 on 32u4 Feathers
#define LED_COUNT 32        // 8x4 grid on Neopixel Featherwing
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

uint32_t green = strip.Color(0, 64, 0);
uint32_t yellow = strip.Color(64, 64, 0);
uint32_t red = strip.Color(64, 0, 0);
uint32_t off = strip.Color(0,0,0);

int row0;
int row1;
int row2;
int row3;

int targ0;
int targ1;
int targ2;
int targ3;

void setup() {
  Wire.begin(0x14);
  Wire.onReceive(DataReceive);
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(3);

  row0 = row1 = row2 = row3 = 0;
  targ0 = targ1 = targ2 = targ3 = 50;
}

void loop() {
  row0 = nextVal(row0, targ0);
  row1 = nextVal(row1, targ1);     
  row2 = nextVal(row2, targ2);    
  row3 = nextVal(row3, targ3);
  
  setRow( 0, row0);
  setRow( 8, row1);
  setRow(16, row2);
  setRow(24, row3);
}

int nextVal(int val, int targ) {
  int change = random(0, 6);
  if (targ > val)
    return (val + change);
  else
    return (val - change);
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

void DataReceive(int numBytes)
{
  int target;
  int value;
  while(Wire.available()) 
  { 
    target = Wire.read();
    value = Wire.read();
    switch(target){
      case 0:
        targ0 = value;
        break;
      case 1:
        targ1 = value;
        break;
      case 2:
        targ2 = value;
        break;
      case 3:
        targ3 = value;
        break;
      default:
        targ0 = random(0, 100);
        targ1 = random(0, 100);
        targ2 = random(0, 100);
        targ3 = random(0, 100);
        break;
    }
  }
}
