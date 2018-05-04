// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
// Modified by Ryan Jones for sound activated All About Circuits project 2017
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN_right_chick_1 0
#define PIN_right_chick_2 1
#define PIN_right_chick_3 2

#define PIN_left_chick_1 6
#define PIN_left_chick_2 7
#define PIN_left_chick_3 8

#define NUMPIXELS 6

int sound = 0;
int sensorPin = A1;


Adafruit_NeoPixel right_chick_1 = Adafruit_NeoPixel(NUMPIXELS, PIN_right_chick_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel right_chick_2 = Adafruit_NeoPixel(NUMPIXELS, PIN_right_chick_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel right_chick_3 = Adafruit_NeoPixel(NUMPIXELS, PIN_right_chick_3, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel left_chick_1 = Adafruit_NeoPixel(NUMPIXELS, PIN_left_chick_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel left_chick_2 = Adafruit_NeoPixel(NUMPIXELS, PIN_left_chick_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel left_chick_3 = Adafruit_NeoPixel(NUMPIXELS, PIN_left_chick_3, NEO_GRB + NEO_KHZ800);

int delayval = 10; // delay for half a second

// uint32_t Wheel(byte WheelPos) {
//   WheelPos = 255 - WheelPos;
//   if(WheelPos < 85) {
//     return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
//   }
//   if(WheelPos < 170) {
//     WheelPos -= 85;
//     return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
//   }
//   WheelPos -= 170;
//   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
// }

// void red() {
//   for (int i = 0; i < NUMPIXELS; i++) {
//     // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
//     pixels.setPixelColor(i, pixels.Color(255, 0, 0)); // Moderately bright green color.
//     pixels.show(); // This sends the updated pixel color to the hardware.
//     delay(delayval); // Delay for a period of time (in milliseconds).
//   }
// }


// void rainbow(uint8_t wait) {
//   uint16_t i, j;
//   for(j=0; j<256; j++) {
//     for(i=0; i<strip.numPixels(); i++) {
//       strip.setPixelColor(i, Wheel((i+j) & 255));
//     }
//     strip.show();
//     delay(10);
//     // wait is 20
//   }
// }

void off() {
  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      right_chick_1.setPixelColor(i, right_chick_1.Color(0, 0, 0));
      right_chick_2.setPixelColor(i, right_chick_2.Color(0, 0, 0));
      right_chick_3.setPixelColor(i, right_chick_3.Color(0, 0, 0));

      left_chick_1.setPixelColor(i, left_chick_1.Color(0, 0, 0));
      left_chick_2.setPixelColor(i, left_chick_2.Color(0, 0, 0));
      left_chick_3.setPixelColor(i, left_chick_3.Color(0, 0, 0));

      right_chick_1.show();
      right_chick_2.show();
      right_chick_3.show();

      left_chick_1.show();
      left_chick_2.show();
      left_chick_3.show();
    // delay(delayval); // Delay for a period of time (in milliseconds).
  }
}

void color_phaser(int analog_in, int adjuster) {
   int analog_in_level = (analog_in-adjuster)/3;
   Serial.print("this level: ");
  Serial.println(analog_in-adjuster);
   for (int i=0; i<analog_in_level; i++) {
      

      right_chick_1.setPixelColor(i, right_chick_1.Color(i*40, 0, 100-i*50));
      right_chick_2.setPixelColor(i, right_chick_2.Color(i*40, 0, 100-i*50));
      right_chick_3.setPixelColor(i, right_chick_3.Color(i*40, 60-i*10, 60-i*10));

      left_chick_1.setPixelColor(i, left_chick_1.Color(i*40, 60-i*10, 60-i*10));
      left_chick_2.setPixelColor(i, left_chick_2.Color(i*40, 0, 100-i*50));
      left_chick_3.setPixelColor(i, left_chick_3.Color(i*40, 0, 100-i*50));

      right_chick_1.show();
      right_chick_2.show();
      right_chick_3.show();

      left_chick_1.show();
      left_chick_2.show();
      left_chick_3.show();
      
      

   }
   delay(30);
}

void setup() {
   pinMode (sensorPin, INPUT) ;
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
      right_chick_1.begin();
      right_chick_2.begin();
      right_chick_3.begin();

      left_chick_1.begin();
      left_chick_2.begin();
      left_chick_3.begin();
  Serial.begin(9600);
  Serial.println("start sound detection");
}

int adjuster = 0;
void loop() {
  unsigned long currentMillis = millis();
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  sound = analogRead(sensorPin);
  if (adjuster==0) {
    adjuster = sound;
  }
  Serial.println(sound);
  color_phaser(sound, adjuster);
  off();
}
