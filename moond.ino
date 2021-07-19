#include <FastLED.h>

#define NUM_LEDS 23 
#define DATA_PIN 6
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
   FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);   // GRB ordering is assumed
  Serial.begin(9600);
}

void loop() {
      
  int sensorValue = analogRead(A0);                       //read raw voltage
  int light = analogRead(A1);                             //read raw light valiue
  float voltage = sensorValue * (5.0 / 1110.0);           //converts voltage to the range 0-5V 
  light = constrain(light, 0, 150);                       //limits the light valiues from 0-150 --> makes it that light peaks wont be recepted
  Serial.print(light);                            
  Serial.print("\t");;                            
  light = map(light, 0, 150, 30, 0 );                     //connverts range 0-150 to 30-0 (the darker it gets, the brighter the moon shines)
  FastLED.setBrightness(light);                           //sets the light valiu to the moons brightness
  Serial.println(voltage);                        

  if (voltage < 3){
    
    for(int i=0; i<NUM_LEDS; i++) {                       // For each pixel...
      FastLED.setBrightness(100);                         //sets brightness to 100 (light sensor wont affect this mode)
      leds[i] = CRGB::Red;                                //sets all leds one by one to red
      FastLED.show();
      delay(100);                                         //delay till next led is turned on
      }
    for(int i=0; i<NUM_LEDS; i++) {                       // For each pixel...
      leds[i] = CRGB::Black;                              //turns off led
      FastLED.show();
      delay(100);                                         //delay till next led is turned on
      } 
  } 
    else{
      for(int i=0; i<NUM_LEDS; i++) {                     // For each pixel...
       leds[i] = CRGB::White;                             //nice colors: DarkOrange,LightGoldenrodYellow,SlateBlue, Yellow
       FastLED.show();
      }
    }
  }
