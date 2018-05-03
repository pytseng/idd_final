// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
// Modified by Ryan Jones for sound activated All About Circuits project 2017
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN_contour 6
#define PIN_secondary 7
#define PIN_left_chick_1 6
#define PIN_left_chick_2 7
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      60
//
//#include <RBD_Timer.h> // https://github.com/alextaujenis/RBD_Timer
//
//RBD::Timer timer;
int sound = 0;
int sensorPin = A1;

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN_contour, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN_contour, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel pixels_secondary = Adafruit_NeoPixel(NUMPIXELS, PIN_secondary, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_secondary = Adafruit_NeoPixel(60, PIN_secondary, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel left_chick_1 = Adafruit_NeoPixel(6, PIN_left_chick_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel left_chick_2 = Adafruit_NeoPixel(6, PIN_left_chick_2, NEO_GRB + NEO_KHZ800);

int delayval = 10; // delay for half a second

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void red() {
  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(255, 0, 0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
  }
}
void green() {
  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0, 150, 0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
  }
}
void yellow() {
  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(255, 100, 0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
  }
}
void off() {
  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
  }
}
void rainbow(uint8_t wait) {
  uint16_t i, j;
  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(10);
    // wait is 20
  }
}

void react_color(int analog_in) {
  for (int i = 0; i < NUMPIXELS; i++) {
    if (i==3||i==7){
      Serial.print(i);
      pixels.setPixelColor(3, pixels.Color(255, 0, 0));
      pixels.setPixelColor(7, pixels.Color(255, 0, 0));      
    }
    else {
      pixels.setPixelColor(i, pixels.Color(analog_in%255, 20, 20)); // Moderately bright green color.  
    }
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels_secondary.setPixelColor(i, pixels_secondary.Color(20, analog_in%255, 20)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel coclor to the hardware.
    pixels_secondary.show();
    // delay(delayval); // Delay for a period of time (in milliseconds).
  }
}

void color_phaser(int analog_in) {
   for (int i=0; i<analog_in; i+=100) {
      left_chick_1.setPixelColor(i, left_chick_1.Color(200, 0, 0));
      left_chick_2.setPixelColor(i, left_chick_2.Color(200, 0, 0));
   }
}

void setup() {
   pinMode (sensorPin, INPUT) ;
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
  left_chick_1.begin(); // This initializes the NeoPixel library.
  left_chick_2.begin();
  Serial.begin(9600);
  Serial.println("start sound detection");
}

void loop() {
  
  unsigned long currentMillis = millis();
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  sound = analogRead(sensorPin);
  Serial.println(sound);
  delay(10);
  color_phaser(sound);
}
