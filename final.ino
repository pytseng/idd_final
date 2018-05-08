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

#define PIN_hat_1 10
#define PIN_hat_2 11
#define PIN_hat_3 12
#define PIN_hat_4 13
#define PIN_hat_lower 9

#define NUMPIXELS 6
#define NUMPIXELS_hat 10

int wait = 20;
int sound = 0;
int sensorPin = A1;
int tune_mode = 0;
int tunePin = A5;


Adafruit_NeoPixel right_chick_1 = Adafruit_NeoPixel(NUMPIXELS, PIN_right_chick_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel right_chick_2 = Adafruit_NeoPixel(NUMPIXELS, PIN_right_chick_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel right_chick_3 = Adafruit_NeoPixel(NUMPIXELS, PIN_right_chick_3, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel left_chick_1 = Adafruit_NeoPixel(NUMPIXELS, PIN_left_chick_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel left_chick_2 = Adafruit_NeoPixel(NUMPIXELS, PIN_left_chick_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel left_chick_3 = Adafruit_NeoPixel(NUMPIXELS, PIN_left_chick_3, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel hat_1 = Adafruit_NeoPixel(NUMPIXELS_hat, PIN_hat_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel hat_2 = Adafruit_NeoPixel(NUMPIXELS_hat, PIN_hat_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel hat_3 = Adafruit_NeoPixel(NUMPIXELS_hat, PIN_hat_3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel hat_4 = Adafruit_NeoPixel(NUMPIXELS_hat, PIN_hat_4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel hat_lower = Adafruit_NeoPixel(NUMPIXELS_hat, PIN_hat_lower, NEO_GRB + NEO_KHZ800);


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
  for (int i=0; i<NUMPIXELS; i++) {
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

  for (int i=0; i<NUMPIXELS_hat; i++) {
    hat_1.setPixelColor(i, hat_1.Color(0, 0, 0));
    hat_2.setPixelColor(i, hat_2.Color(0, 0, 0));
    hat_3.setPixelColor(i, hat_3.Color(0, 0, 0));
    hat_4.setPixelColor(i, hat_4.Color(0, 0, 0));
    hat_lower.setPixelColor(i, hat_lower.Color(0, 0, 0));

    hat_1.show();
    hat_2.show();
    hat_3.show();
    hat_4.show();
    hat_lower.show();
  }
}

void color_phaser(int analog_in, int adjuster) {
   int analog_in_level = (analog_in-adjuster)/3;
  //  Serial.print("this level: ");
  // Serial.println(analog_in-adjuster);
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

// For the hat

void hat_pattern_1 (int analog_in, int adjuster) {
  int analog_in_level = (abs(analog_in-adjuster))/2;
  Serial.println(analog_in_level);

  for (int i=0; i<analog_in_level%10; i++) {
    hat_1.setPixelColor(NUMPIXELS_hat-i, hat_1.Color(i*20, 60-i*5, 60-i*5));
    hat_2.setPixelColor(NUMPIXELS_hat-i, hat_2.Color(i*20, 60-i*5, 60-i*5));
    hat_3.setPixelColor(NUMPIXELS_hat-i, hat_3.Color(i*20, 60-i*5, 60-i*5));
    hat_4.setPixelColor(NUMPIXELS_hat-i, hat_4.Color(i*20, 60-i*5, 60-i*5));
    hat_lower.setPixelColor(NUMPIXELS_hat-i, hat_lower.Color(i*20, 60-i*5, 60-i*5));
    
  
    hat_1.show();
    hat_2.show();
    hat_3.show();
    hat_4.show();
    hat_lower.show();
  }
}


void hat_pattern_3 (int analog_in, int adjuster) {
  int analog_in_level = (analog_in-adjuster)/3;
  Serial.println(analog_in-adjuster);
  // for (int i=0; i<NUMPIXELS_hat; i++) {
  //   hat_1.setPixelColor(i, hat_1.Color(50, 10, 10));
  //   hat_2.setPixelColor(i, hat_2.Color(50, 10, 10));
  //   hat_3.setPixelColor(i, hat_3.Color(50, 10, 10));
  //   hat_4.setPixelColor(i, hat_4.Color(50, 10, 10));
  //   hat_lower.setPixelColor(i, hat_lower.Color(50, 10, 10));
    
  
  //   hat_1.show();
  //   hat_2.show();
  //   hat_3.show();
  //   hat_4.show();
  //   hat_lower.show();
  // }
  for (int i=0; i<NUMPIXELS_hat; i++) {
    hat_1.setPixelColor(i, hat_1.Color(0, 60, 60));
    hat_2.setPixelColor(i, hat_2.Color(0, 60, 60));
    hat_3.setPixelColor(i, hat_3.Color(0, 60, 60));
    hat_4.setPixelColor(i, hat_4.Color(0, 60, 60));
    hat_lower.setPixelColor(i, hat_lower.Color(0, 60, 60));
    
  
  }

  for (int i=0; i<abs(analog_in_level)%10; i++) {
    hat_2.setPixelColor(0, hat_2.Color(60-i*5, 60+i*5, 0));
    hat_3.setPixelColor(0, hat_3.Color(60-i*5, 60+i*5, 0));
    hat_3.setPixelColor(1, hat_3.Color(60-i*5, 60+i*5, 0));
    hat_4.setPixelColor(0, hat_4.Color(60-i*5, 60+i*5, 0));
    hat_4.setPixelColor(1, hat_4.Color(60-i*5, 60+i*5, 0));
    hat_4.setPixelColor(2, hat_4.Color(60-i*5, 60+i*5, 0));

    hat_1.setPixelColor(i, hat_1.Color(60-i*5, 60+i*5, 0));
    hat_2.setPixelColor(i+1, hat_2.Color(60-i*5, 60+i*5, 0));
    hat_3.setPixelColor(i+2, hat_3.Color(60-i*5, 60+i*5, 0));
    hat_4.setPixelColor(i+3, hat_4.Color(60-i*5, 60+i*5, 0));
    hat_lower.setPixelColor(i, hat_lower.Color(60-i*5, 60+i*5, 0));
    
  
    hat_1.show();
    hat_2.show();
    hat_3.show();
    hat_4.show();
    hat_lower.show();
  }
}

uint32_t Wheel(byte WheelPos, Adafruit_NeoPixel& hat) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return hat.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return hat.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return hat.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}


// void rainbow(uint8_t wait) {
//   uint16_t i, j;
 
//   for(j=0; j<256; j++) {
//     for(i=0; i<strip.numPixels(); i++) {
//       strip.setPixelColor(i, Wheel((i+j) & 255));
//     }
//     strip.show();
//     delay(wait);
//   }
// }
 
// Slightly different, this makes the rainbow equally distributed throughout
 


void setup() {
   pinMode (sensorPin, INPUT) ;
   pinMode (tunePin, INPUT);
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

      hat_1.begin();
      hat_2.begin();
      hat_3.begin();
      hat_4.begin();
      hat_lower.begin();
  Serial.begin(9600);
  Serial.println("start sound detection");
}

int adjuster = 0;

void loop() {
  unsigned long currentMillis = millis();
  sound = analogRead(sensorPin);
  tune_mode = analogRead(tunePin);
  
  if (adjuster==0) {
    adjuster = sound;
  }
  Serial.println(adjuster);
  Serial.println(sound);
  // Serial.print(tune_mode);

  if (tune_mode<=350) {
    // mode 1 horizontal wave
    // Serial.println("tune_mode_1");


    hat_pattern_1(sound, adjuster);

  }
  else if (tune_mode>350 && tune_mode<=700) {
    // Serial.println("tune_mode_2");
      for (int color=0; color<255; color++) {
        for (int i=0; i<NUMPIXELS_hat; i++) {
          hat_1.setPixelColor(i, Wheel(color,hat_1));
          hat_2.setPixelColor(i, Wheel(color,hat_2));
          hat_3.setPixelColor(i, Wheel(color,hat_3));
          hat_4.setPixelColor(i, Wheel(color,hat_4));
         }
      hat_1.show();
      hat_2.show();
      hat_3.show();
      hat_4.show();
    }
  }
  else {
    // mode 3 vertical wave
    // hat_pattern_1(sound, adjuster);
    // Serial.println("tune_mode_3");
    hat_pattern_3(sound, adjuster);
  }
  color_phaser(sound, adjuster);
  off();
}


